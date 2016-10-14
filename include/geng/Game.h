#ifndef GAME_H
#define GAME_H

#include "GameBase.h"

namespace grynca {

    class Window;

    template <typename Derived>
    class Game : public GameBase<Derived>
    {
    protected:
        Game(const std::string& name = "Grynca Game", uint32_t width = 1024, uint32_t height = 768);
        Game(const Game&) {}

    private:
        template <typename D> friend class GameBase;

        void updateIter_();
        void renderIter_(float dt);
        Window& getWindow_();
    };

}

#include "Game.inl"
#endif //GAME_H
