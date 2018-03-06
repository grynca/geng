#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "types/CommonPtr.h"
#include "types/Timer.h"
#include "types/Singleton.h"
#include <functional>

#define ENTITY_ROLES_ENUM(NAME, ...)  DEFINE_ENUM_E(NAME, GengEntityRoles, __VA_ARGS__)

namespace grynca {

    //fw
    class GameBase;
    class PhysicsManager;

    class GameBase : public Singleton<GameBase>
    {
    public:
        enum SystemsPipeline {
            spUpdate,
            spRender,

            spCount
        };

        enum ProfileType {
            ptUpdate,
            ptRender,
            ptTick,

            ptCount
        };

    public:
        GameBase();
        virtual ~GameBase();

        template <typename EntityTypes>
        void initEntityTypes(uint32_t initial_ents_reserve = 100);

        const Timer& getTimer()const;
        const EntityManager& getEntitiesManager()const;
        const PhysicsManager& getPhysicsManager()const;

        Timer& accTimer();
        EntityManager& accEntitiesManager();
        PhysicsManager& accPhysicsManager();

        template <typename T, typename... ConstrArgs>
        T& initModule(ConstrArgs&&... cargs);

        template <typename T>
        T& accModule();
        template <typename T>
        const T& getModule()const;
        template <typename T>
        bool containsModule()const;

        u32 getFPS()const;
        u32 getUPS()const;
        f32 getTargetTicklen()const;
        f32 getTargetUPS()const;

        void SetTargetUps(f32 ups);     // should be set before start()
        f32 getLag();

        template <typename SystemType>
        SystemType& addUpdateSystem();
        template <typename SystemType>
        SystemType& addRenderSystem();


        template <typename SystemType>
        SystemType* getUpdateSystem();
        template <typename SystemType>
        SystemType* getRenderSystem();

        void start();
        void quit();

        // creates entity
        template <typename EntAccType>
        EntAccType createEntity();

        template <typename EntAccType, u32 N>
        std::array<EntAccType, N> createEntities();

        // creates and calls EntType.init(args)
        template <typename EntAccType, typename... CallArgs>
        EntAccType createAndInitEntity(CallArgs &&... args);

        template <typename EntAccType>
        EntAccType getEntity(EntityIndex eid)const;
        Entity getEntity(EntityIndex eid)const;

        // LoopFunc(Entity& e)
        template <typename EntityType, typename LoopFunc>
        void loopEntities(const LoopFunc& lf);
        template <typename LoopFunc>
        void loopEntities(u16 entity_type_id, const LoopFunc& lf);

        u32 getUpdateNum()const;
        u32 getFrameNum()const;

        GameBase& asGameBase();
        const GameBase& asGameBase()const;

        SortedCallbacks<void(const ProfilingSample&)>& accProfilingCallbacks(u32 type/*ProfileType*/);
    protected:
        struct ModuleTypesDomain {};
        struct EntityTypesDomain {};

        GameBase(const GameBase &) = delete;

        template <typename EntityTypes>
        void addEMTypes_(u32 initial_ents_reserve);

        virtual void init() {}          // runs at start (this is where you e.g. add systems)
        virtual void tick() {}          // runs once per second
        virtual void update() {}        // runs UPS times per second (default 60)
                                        // and before update systems
        virtual void render(f32 dt) {}  // runs as fast as possible
                                        // and before render systems

        virtual void initEMInner_(u32 initial_ents_reserve);
        virtual void initInner_();
        virtual void updateInner_();
        virtual void tickInner_();
        virtual void renderInner_(f32 dt);

        template <typename T, std::size_t...Is>
        std::array<T, sizeof...(Is)> makeEntsInner_(GameBase& me, std::index_sequence<Is...>);

        bool quit_;

        u32 fps_;
        u32 ups_;
        f32 target_ups_;
        f32 target_ticklen_;

        f32 seconds_timer_, update_timer_, frame_timer_;
        f32 update_lag_;     // how many updates game is behind
        u32 frames_total_, updates_total_, frames_this_sec_, updates_this_sec_;

        fast_vector<CommonPtr> modules_;

        // Internal modules
        Timer timer_;
        EntityManager entity_manager_;
        PhysicsManager* physics_manager_;

// Profiling
        u32 profiling_measure_ids_[ptCount];
        SortedCallbacks<void(const ProfilingSample&)> profiling_callbacks[ptCount];

    private:
        typedef void (*EntityKilledCb) (Entity& ent);

        struct InitEntityType {
            template <typename TP, typename T>
            static void f(GameBase& game, u32 types_offset);
        };

        fast_vector<EntityKilledCb> on_entity_killed_;
    };

}
#endif //GAMEBASE_H

#if !defined(GAME_BASE_INL) && !defined(WITHOUT_IMPL)
#define GAME_BASE_INL
# include "GameBase.inl"
#endif // GAME_INL
