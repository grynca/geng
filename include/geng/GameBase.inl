#include "GameBase.h"
#include <chrono>
#include <thread>

#ifdef WEB
#include <emscripten/emscripten.h>
    static void dispatch_main(void* fp) {
        std::function<void()>* func = (std::function<void()>*)fp;
        (*func)();
    }
#endif

namespace grynca {

    inline Timer& GameBase::getTimer() {
        return timer_;
    }
    
    template <typename T>
    inline T& GameBase::getModule() {
        // lazy get
        u32 tid = Type<T, GameBase>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].template getAs<T>())
            modules_[tid] = CommonPtr(new T());

        CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    template <typename T>
    inline bool GameBase::containsModule() {
        u32 tid = Type<T, GameBase>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        CommonPtr& ptr = modules_[tid];
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

    inline void GameBase::setUPS(f32 ups) {
        target_ups_ = ups;
        target_ticklen_ = 1.0f/ups;
    };

    inline f32 GameBase::getLag() {
        return lag_;
    }
    
    inline GameBase::GameBase()
     :  quit_(false), fps_(0), ups_(0), target_ups_(60), target_ticklen_(1.0f/60),
        seconds_timer_(0.0f), update_timer_(0.0f), frame_timer_(0.0f),
        frames_(0), updates_(0)
    {
    }

    template <typename EntityTypes>
    void GameBase::initEM(u32 initial_ents_reserve) {
        entity_manager_.init<EntityTypes>(initial_ents_reserve);
        EntityTypes::template callOnTypes<SetTypeIds>();
    }

    inline GameBase::~GameBase() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    };

    template <typename SystemType>
    inline SystemType& GameBase::addUpdateSystem() {
        return entity_manager_.template addSystem<SystemType>(spUpdate);
    };

    template <typename SystemType>
    inline SystemType& GameBase::addRenderSystem() {
        return entity_manager_.template addSystem<SystemType>(spRender);
    };

    template <typename SystemType>
    SystemType* GameBase::findUpdateSystem() {
        for (u32 i=0; i<entity_manager_.getSystemsPipelineSize(spUpdate); ++i) {
            SystemType* s = dynamic_cast<SystemType*>(entity_manager_.getSystem(spUpdate, i));
            if (s)
                return s;
        }
        return NULL;
    }

    template <typename SystemType>
    SystemType* GameBase::findRenderSystem() {
        for (u32 i=0; i<entity_manager_.getSystemsPipelineSize(spRender); ++i) {
            SystemType* s = dynamic_cast<SystemType*>(entity_manager_.getSystem(spRender, i));
            if (s)
                return s;
        }
        return NULL;
    }

    inline void GameBase::start() {
        init();
        seconds_timer_ = update_timer_ = frame_timer_ = lag_ = frames_ = updates_ = 0;
        timer_.reset();

        std::function<void()> main_loop = [this]() {
#ifdef WEB
            if (quit_) {
                emscripten_cancel_main_loop();
                return;
            }
#endif
            f32 now = timer_.getElapsed();
            f32 dt_update = now - update_timer_;
            while (dt_update > target_ticklen_) {
                updateInner_();
                now = timer_.getElapsed();
                dt_update = now - update_timer_;
            }

            lag_ = dt_update*target_ups_;
            f32 dt_frame = now - frame_timer_;

            renderInner_(dt_frame);
            if (now - seconds_timer_ > 1.0f) {
                tickInner_();
            }

        };

#ifdef WEB
        emscripten_set_main_loop_arg(dispatch_main, &main_loop,
                                     0 /* use browser's framerate */,
                                     1 /* simulate infinite loop */);
#else
        while (!quit_) {
            main_loop();
        }
#endif
    };

    inline void GameBase::quit() {
        quit_ = true;
    };

    template <typename EntType>
    inline Entity GameBase::createEntity(const EntityFunc& init_f) {
        Entity e = getEntitiesManager().newEntity(EntType::typeId());
        init_f(e, *this);
        e.create();
        return e;
    }

    inline void GameBase::udpateEntity(EntityIndex id, const EntityFunc& update_f) {
        Entity e = getEntity(id);
        update_f(e, *this);
    }

    inline void GameBase::udpateEntitySafe(EntityIndex id, const EntityFunc& update_f) {
        Entity e = getEntitiesManager().tryGetEntity(id);
        if (e.isValid())
            update_f(e, *this);
    }

    inline EntityManager& GameBase::getEntitiesManager() {
        return entity_manager_;
    };

    inline Entity GameBase::getEntity(EntityIndex ent_id) {
        return entity_manager_.getEntity(ent_id);
    };

    inline void GameBase::updateInner_() {
        update();
        entity_manager_.updateSystemsPipeline(spUpdate, target_ticklen_);

        updates_++;
        update_timer_ += target_ticklen_;
    };

    inline void GameBase::tickInner_() {
        seconds_timer_ += 1.0f;
        fps_ = frames_;
        ups_ = updates_;
        frames_ = updates_ = 0;
        tick();
#ifdef PROFILE_BUILD
        std::cout << "lag: " << lag_ << ", ups: " << ups_ << ", fps: " << fps_ << std::endl;
#endif
    }
    
    inline void GameBase::renderInner_(f32 dt) {
        render();
        entity_manager_.updateSystemsPipeline(spRender, dt);
        frames_++;
        frame_timer_ += dt;
    };

    template <typename TP, typename T>
    inline void GameBase::SetTypeIds::f() {
        T::typeId() = u32(TP::template pos<T>());
    }
}