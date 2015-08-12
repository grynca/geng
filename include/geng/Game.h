#ifndef GAME_H
#define GAME_H

#include "types/containers/fast_vector.h"
#include "types/CommonPtr.h"
#include "types/Timer.h"

namespace grynca {

    class Game {
    public:
        void start();

        template <typename T>
        T& getModule();

        uint32_t getFPS()const;
        uint32_t getUPS()const;

        virtual ~Game();
    protected:
        Game(const std::string& name = "Grynca Game", uint32_t width = 1024, uint32_t height = 768);
        Game(const Game&) {}
        virtual void init() {}     // runs at start
        virtual void tick() {}     // runs once per second
        virtual void update() {}   // runs 60 times per second
        virtual void render() {}   // runs as fast as possible (when vsync is not enabled)
    private:
        void gameLoop_();
        template <typename T>
        bool containsModule_();


        Timer timer_;
        fast_vector<CommonPtr> modules_;
        uint32_t fps_;
        uint32_t ups_;
    };

}

#include "Game.inl"
#endif //GAME_H
