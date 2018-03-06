#include "GameBase.h"
#include "core/GengSystem.h"
#include <chrono>
#include <thread>
#include <array>

#ifdef WEB
#include <emscripten/emscripten.h>
    static void dispatch_main(void* fp) {
        std::function<void()>* func = (std::function<void()>*)fp;
        (*func)();
    }
#endif

#include "physics/physics_includes.h"
#if GENG_NW==1
#   include "network/network_includes.h"
#endif

namespace grynca {

    inline const Timer& GameBase::getTimer()const {
        return timer_;
    }

    inline const EntityManager& GameBase::getEntitiesManager()const {
        return entity_manager_;
    }

    inline const PhysicsManager& GameBase::getPhysicsManager()const {
        return *physics_manager_;
    }

    inline Timer& GameBase::accTimer() {
        return timer_;
    }

    inline EntityManager& GameBase::accEntitiesManager() {
        return entity_manager_;
    }

    inline PhysicsManager& GameBase::accPhysicsManager() {
        return *physics_manager_;
    }

    template <typename T, typename... ConstrArgs>
    inline T& GameBase::initModule(ConstrArgs&&... cargs) {
        u32 tid = Type<T, ModuleTypesDomain>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].template getAs<T>())
            modules_[tid] = CommonPtr(new T(std::forward<ConstrArgs>(cargs)...));

        CommonPtr& ptr = modules_[tid];
        return *(ptr.accAs<T>());
    }

    template <typename T>
    inline T& GameBase::accModule() {
        return const_cast<T&>(getModule<T>());
    }

    template <typename T>
    inline const T& GameBase::getModule()const {
        u32 tid = Type<T, ModuleTypesDomain>::getInternalTypeId();
        ASSERT(containsModule<T>());
        const CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    template <typename T>
    inline bool GameBase::containsModule()const {
        u32 tid = Type<T, ModuleTypesDomain>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        const CommonPtr& ptr = modules_[tid];
        return ptr.getAs<T>() != NULL;
    }

    inline u32 GameBase::getFPS()const {
        return fps_;
    }

    inline u32 GameBase::getUPS()const {
        return ups_;
    }

    inline f32 GameBase::getTargetTicklen()const {
        return target_ticklen_;
    }

    inline f32 GameBase::getTargetUPS()const {
        return target_ups_;
    }

    inline void GameBase::SetTargetUps(f32 ups) {
        target_ups_ = ups;
        target_ticklen_ = 1.0f/ups;
    };

    inline f32 GameBase::getLag() {
        return update_lag_;
    }
    
    inline GameBase::GameBase()
     :  quit_(false), fps_(0), ups_(0), target_ups_(60), target_ticklen_(1.0f/60),
        seconds_timer_(0.0f), update_timer_(0.0f), frame_timer_(0.0f),
        frames_total_(0), updates_total_(0), frames_this_sec_(0), updates_this_sec_(0)
    {
        PROFILE_ID_INIT(profiling_measure_ids_[ptUpdate], "Update");
        PROFILE_ID_INIT(profiling_measure_ids_[ptRender], "Render");
        PROFILE_ID_INIT(profiling_measure_ids_[ptTick], "Tick");

        /// Init Modules
        initModule<EntityResourcesManager>();
        physics_manager_ = new PhysicsManager();
        physics_manager_->init(*this);
#if GENG_NW==1
        initModule<Server>();
#endif

        SIMPLE_FUNCTOR(OnEntityKilled, (GameBase* me, Entity& ent) {
            me->on_entity_killed_[ent.getIndex().getEntityTypeId()](ent);
        });

        accEntitiesManager().accBeforeEntityKilled().bind<OnEntityKilled>(this);
    }

    inline GameBase::~GameBase() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
        delete physics_manager_;
    }

    template <typename EntityTypes>
    void GameBase::initEntityTypes(u32 initial_ents_reserve) {
        initEMInner_(initial_ents_reserve);
        addEMTypes_<EntityTypes>(initial_ents_reserve);
    }

    template <typename SystemType>
    inline SystemType& GameBase::addUpdateSystem() {
        return entity_manager_.template addSystem<SystemType>(spUpdate);
    }

    template <typename SystemType>
    inline SystemType& GameBase::addRenderSystem() {
        return entity_manager_.template addSystem<SystemType>(spRender);
    };

    template <typename SystemType>
    SystemType* GameBase::getUpdateSystem() {
        return entity_manager_.template getSystemByType<SystemType>(spUpdate);
    }

    template <typename SystemType>
    SystemType* GameBase::getRenderSystem() {
        return entity_manager_.template getSystemByType<SystemType>(spRender);
    }

    inline void GameBase::start() {
        initInner_();

        mainLoop([this]() {
            return !quit_;
        },
        [this]() {
            f32 now = timer_.getElapsed();
            f32 dt_update = now - update_timer_;
            // TODO: detect and handle spiral of death
            while (dt_update > target_ticklen_) {
                PROFILE_SAMPLE_F(profiling_measure_ids_[ptUpdate], profiling_callbacks[ptUpdate]);
                updateInner_();
                now = timer_.getElapsed();
                dt_update = now - update_timer_;
            }
            {
                PROFILE_SAMPLE_F(profiling_measure_ids_[ptRender], profiling_callbacks[ptRender]);
                update_lag_ = dt_update*target_ups_;
                f32 dt_frame = now - frame_timer_;
                renderInner_(dt_frame);
            }
            if (now - seconds_timer_ > 1.0f) {
                PROFILE_SAMPLE_F(profiling_measure_ids_[ptTick], profiling_callbacks[ptTick]);
                tickInner_();
            }
        });
    };

    inline void GameBase::quit() {
        quit_ = true;
    };

    template <typename EntAccType>
    inline EntAccType GameBase::createEntity() {
        u16 tid = u16(Type<EntAccType, EntityTypesDomain>::getTypeInfo().getId());
        Entity e = accEntitiesManager().newEntity(tid);
        return e.get<EntAccType>();
    }

    template <typename EntAccType, u32 N>
    inline std::array<EntAccType, N> GameBase::createEntities() {
        return makeEntsInner_<EntAccType>(*this, std::make_index_sequence<N>());
    }

    template <typename EntAccType, typename... CallArgs>
    inline EntAccType GameBase::createAndInitEntity(CallArgs &&... args) {
        u16 tid = u16(Type<EntAccType, EntityTypesDomain>::getTypeInfo().getId());
        Entity e = accEntitiesManager().newEntity(tid);
        EntAccType ent_wrap = e.get<EntAccType>();
        ent_wrap.init(std::forward<CallArgs>(args)...);
        return ent_wrap;
    }

    template <typename EntAccType>
    inline EntAccType GameBase::getEntity(EntityIndex eid)const {
        Entity e = getEntitiesManager().getEntity(eid);
        return e.get<EntAccType>();
    }

    inline Entity GameBase::getEntity(EntityIndex eid)const {
        return getEntitiesManager().getEntity(eid);
    }

    template <typename EntityType, typename LoopFunc>
    inline void GameBase::loopEntities(const LoopFunc& lf) {
        u16 tid = u16(Type<EntityType, EntityTypesDomain>::getTypeInfo().getId());
        accEntitiesManager().loopEntities(tid, lf);
    }

    template <typename LoopFunc>
    inline void GameBase::loopEntities(u16 entity_type_id, const LoopFunc& lf) {
        accEntitiesManager().loopEntities(entity_type_id, lf);
    }

    inline u32 GameBase::getUpdateNum()const {
        return updates_total_;
    }

    inline u32 GameBase::getFrameNum()const {
        return frames_total_;
    }

    inline GameBase& GameBase::asGameBase() {
        return *this;
    }

    inline const GameBase& GameBase::asGameBase()const {
        return *this;
    }

    inline SortedCallbacks<void(const ProfilingSample&)>& GameBase::accProfilingCallbacks(u32 type) {
        ASSERT(type < ptCount);
        return profiling_callbacks[type];
    }

    template <typename EntityTypes>
    inline void GameBase::addEMTypes_(u32 initial_ents_reserve) {
        u16 types_offset = entity_manager_.getEntityTypesCount();
        entity_manager_.addEntityTypes<EntityTypes>(initial_ents_reserve);
        EntityTypes::template callOnTypes<InitEntityType>(*this, types_offset);
    }

    inline void GameBase::initEMInner_(u32 initial_ents_reserve) {
        addEMTypes_<PhysicsEntityTypes>(initial_ents_reserve);
    }

    inline void GameBase::initInner_() {
        init();
        dout(entity_manager_.getTypesDebugString() << std::endl);
        dout(physics_manager_->getOverlapCallbacksDebugString() << std::endl);
        seconds_timer_ = update_timer_ = frame_timer_ = update_lag_ = frames_this_sec_ = updates_this_sec_ = frames_total_ = updates_total_ = 0;
        timer_.reset();

        // initialize systems
        for (u32 pl_id=0; pl_id<SYSENT_PIPELINES_CNT; ++pl_id) {
            for (u32 sys_id=0; sys_id<entity_manager_.getSystemsPipelineSize(pl_id); ++sys_id) {
                SystemPos sp(pl_id, sys_id);
                SystemBase* sb = entity_manager_.getSystem(sp);
                GengSystemAll* gsa = dynamic_cast<GengSystemAll*>(sb);
                if (gsa) {
                    gsa->init();
                }
                else {
                    GengSystemScheduled* gss = dynamic_cast<GengSystemScheduled*>(sb);
                    gss->init();
                }
            }
        }
    }

    inline void GameBase::updateInner_() {
        update();
        entity_manager_.updateSystemsPipeline(spUpdate, target_ticklen_);
        updates_total_++;
        updates_this_sec_++;
        update_timer_ += target_ticklen_;
    };

    inline void GameBase::tickInner_() {
        seconds_timer_ += 1.0f;
        fps_ = frames_this_sec_;
        ups_ = updates_this_sec_;
        frames_this_sec_ = updates_this_sec_ = 0;
        tick();
    }
    
    inline void GameBase::renderInner_(f32 dt) {
        render(dt);
        entity_manager_.updateSystemsPipeline(spRender, dt);
        frames_total_++;
        frames_this_sec_++;
        frame_timer_ += dt;
    }

    template <typename T, std::size_t...Is>
    inline std::array<T, sizeof...(Is)> GameBase::makeEntsInner_(GameBase& me, std::index_sequence<Is...>) {
        return {{(static_cast<void>(Is), me.createEntity<T>())...}};
    }

    template <typename TP, typename T>
    inline void GameBase::InitEntityType::f(GameBase& game, u32 types_offset) {
        ASSERT_M(!(Type<T, EntityTypesDomain>::isTypeInfoSet()), "Overriding typeId for entity type.");
        u32 tid = types_offset + u32(TP::template pos<T>());
        TypeInfoManager<EntityTypesDomain>::setTypeId<T>(tid);
        // init entity resources
        game.accModule<EntityResourcesManager>().initSingleton<typename T::Resources>(GameBase::get());
        // register onKill static func
        if (game.on_entity_killed_.size() <= tid) {
            game.on_entity_killed_.enlarge(tid+1);
        }

        SIMPLE_FUNCTOR(CallOnKilled, (Entity& ent) {
            ent.get<T>().onKilled();
        });

        game.on_entity_killed_[tid] = CallOnKilled::f;
    }
}