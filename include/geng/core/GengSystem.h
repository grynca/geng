#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

namespace grynca {

    // fw
    class GameBase;
    class Game;

    class GengSystemAll : public SystemAll {
    public:
        GameBase& getGameBase();
        Game& getGame();

        // gets called at start of game loop
        virtual void init() {}
    };

    class GengSystemScheduled : public SystemScheduled {
    public:
        GameBase& getGameBase();
        Game& getGame() ;

        // gets called at start of game loop
        virtual void init() {}
    };
}

#define WITHOUT_IMPL
#   include "../Game.h"
#undef WITHOUT_IMPL

namespace grynca {

    inline GameBase& GengSystemAll::getGameBase() {
        return GameBase::get();
    };

    inline Game& GengSystemAll::getGame() {
        return Game::get();
    };

    inline GameBase& GengSystemScheduled::getGameBase() {
        return GameBase::get();
    };

    inline Game& GengSystemScheduled::getGame() {
        return Game::get();
    };

}

#endif //GAMESYSTEM_H
