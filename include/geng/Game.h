#ifndef GAME_H
#define GAME_H

#include "types/containers/fast_vector.h"
#include "types/CommonPtr.h"
#include "types/Timer.h"
#include "types/Singleton.h"
#include "sysent.h"


#define ENTITY_ROLES_ENUM(NAME, ...)  DEFINE_ENUM_E(NAME, GengEntityRoles, __VA_ARGS__)

namespace grynca {

    template <typename EntSys, typename Derived>
    class Game : public grynca::Singleton<Derived>
    {
    public:
        using EntSysType = ES<typename EntSys::EntityTypes, typename EntSys::UpdateSystemTypes, typename EntSys::RenderSystemTypes, typename EntSys::EntityRoles>;
        using BaseType = Game<EntSys, Derived>;
        using DerivedType = Derived;
        using GameEntity = Entity<typename EntSys::EntityTypes>;

        void start();

        EntSysType& getSysEnt() { return se_; }
        template <typename T>
        T& getModule();


        uint32_t getFPS()const;
        uint32_t getUPS()const;

        virtual ~Game();

        void quit();
    protected:
        Game(const std::string& name = "Grynca Game", uint32_t width = 1024, uint32_t height = 768);
        Game(const Game&) {}
        virtual void init() {}     // runs at start
        virtual void tick() {}     // runs once per second
        virtual void update() {}   // runs 60 times per second
                                   // before update systems
        virtual void render() {}   // runs as fast as possible (when vsync is not enabled)
                                   // before render systems
    private:
        void gameLoop_();
        template <typename T>
        bool containsModule_();
        Derived& getAsDerived_();

        Timer timer_;
        EntSysType se_;

        fast_vector<CommonPtr> modules_;
        uint32_t fps_;
        uint32_t ups_;
        bool quit_;
    };

}

#include "Game.inl"
#endif //GAME_H
