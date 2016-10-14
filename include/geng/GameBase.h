#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "types/containers/fast_vector.h"
#include "types/CommonPtr.h"
#include "types/Timer.h"
#include "types/Singleton.h"
#include "sysent/Entity.h"

#define ENTITY_ROLES_ENUM(NAME, ...)  DEFINE_ENUM_E(NAME, GengEntityRoles, __VA_ARGS__)

namespace grynca {

    template <typename Derived>
    class GameBase : public Singleton<Derived>
    {
    public:
        using BaseType = GameBase<Derived>;
        using DerivedType = Derived;

        virtual ~GameBase();
        GameBase();

        template <typename EntityTypes>
        void initEM(uint32_t initial_ents_reserve = 10000);

        Timer& getTimer();
        EntityManager& getEntitiesManager();

        template <typename T>
        T& getModule();
        template <typename T>
        bool containsModule();

        uint32_t getFPS()const;
        uint32_t getUPS()const;
        float getTargetTicklen()const;

        void setUPS(float ups);     // should be set before start()
        float getLag();

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

        Entity createEntity(uint16_t ent_type_id);
        Entity getEntity(EntityIndex ent_id);
    protected:
        GameBase(const GameBase &) = delete;

        virtual void init() {}     // runs at start
        virtual void tick() {}     // runs once per second
        virtual void update() {}   // runs UPS times per second (default 60)
                                   // and before update systems
        virtual void render() {}   // runs as fast as possible
                                   // and before render systems

    protected:
        enum {
            spUpdate,
            spRender,

            spCount
        };

        Derived& getAsDerived_();
        void updateIter_();
        void renderIter_(float dt);

        bool quit_;
        Timer timer_;

        uint32_t fps_;
        uint32_t ups_;
        float target_ups_;
        float target_ticklen_;

        float seconds_timer_, update_timer_, frame_timer_;
        float lag_;     // how many updates game is behind
        uint32_t frames_, updates_;

        fast_vector<CommonPtr> modules_;
        EntityManager entity_manager_;
    };

}

#include "GameBase.inl"
#endif //GAMEBASE_H
