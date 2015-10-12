#ifndef GAME_H
#define GAME_H

#include "types/containers/fast_vector.h"
#include "types/CommonPtr.h"
#include "types/Timer.h"
#include "sysent.h"


#define ENTITY_ROLES_ENUM(NAME, ...)  DEFINE_ENUM_E(NAME, GengEntityRoles, __VA_ARGS__)

namespace grynca {

    template <typename EntityTypes,
              typename UpdateSystemTypes,
              typename RenderSystemTypes,
              typename EntityRoles>
    class Game
    {
    public:
        using SysEnt = ES<EntityTypes, UpdateSystemTypes, RenderSystemTypes>;


        void start();

        SysEnt& getSysEnt() { return se_; }
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


        Timer timer_;
        SysEnt se_;

        fast_vector<CommonPtr> modules_;
        uint32_t fps_;
        uint32_t ups_;
        bool quit_;
    };

}

#include "Game.inl"
#endif //GAME_H
