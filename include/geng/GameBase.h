#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "types/containers/fast_vector.h"
#include "types/CommonPtr.h"
#include "types/Timer.h"
#include "types/Singleton.h"
#include "sysent/Entity.h"
#include <functional>

#define ENTITY_ROLES_ENUM(NAME, ...)  DEFINE_ENUM_E(NAME, GengEntityRoles, __VA_ARGS__)

namespace grynca {

    //fw
    class GameBase;

    typedef std::function<void(Entity&, GameBase&)> EntityFunc;

    class GameBase : public Singleton<GameBase>
    {
    public:
        virtual ~GameBase();
        GameBase();

        template <typename EntityTypes>
        void initEM(u32 initial_ents_reserve = 10000);

        Timer& getTimer();
        EntityManager& getEntitiesManager();

        template <typename T>
        T& getModule();
        template <typename T>
        bool containsModule();

        u32 getFPS()const;
        u32 getUPS()const;
        f32 getTargetTicklen()const;

        void setUPS(f32 ups);     // should be set before start()
        f32 getLag();

        template <typename SystemType>
        SystemType& addUpdateSystem();
        template <typename SystemType>
        SystemType& addRenderSystem();


        template <typename SystemType>
        SystemType* findUpdateSystem();
        template <typename SystemType>
        SystemType* findRenderSystem();

        void start();
        void quit();

        template <typename EntType>
        Entity createEntity(const EntityFunc& init_f);
        void udpateEntity(EntityIndex id, const EntityFunc& update_f);
        void udpateEntitySafe(EntityIndex id, const EntityFunc& update_f);  // checks for entity validity
        Entity getEntity(EntityIndex ent_id);
    protected:
        GameBase(const GameBase &) = delete;

        virtual void init() {}     // runs at start
        virtual void tick() {}     // runs once per second
        virtual void update() {}   // runs UPS times per second (default 60)
                                   // and before update systems
        virtual void render() {}   // runs as fast as possible
                                   // and before render systems

        virtual void updateInner_();
        virtual void tickInner_();
        virtual void renderInner_(f32 dt);

        enum {
            spUpdate,
            spRender,

            spCount
        };

        bool quit_;
        Timer timer_;

        u32 fps_;
        u32 ups_;
        f32 target_ups_;
        f32 target_ticklen_;

        f32 seconds_timer_, update_timer_, frame_timer_;
        f32 lag_;     // how many updates game is behind
        u32 frames_, updates_;

        fast_vector<CommonPtr> modules_;
        EntityManager entity_manager_;
    private:
        struct SetTypeIds {
            template <typename TP, typename T>
            static void f();
        };
    };

}

#include "GameBase.inl"
#endif //GAMEBASE_H
