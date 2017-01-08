#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "../Game.h"

namespace grynca {

    class GengSystem : public System {
    public:
        GameBase& getGameBase() {
            return GameBase::get();
        };
        Game& getGame() {
            return Game::get();
        };
    };

    class GengFlaggedSystem : public FlaggedSystem {
    public:
        GameBase& getGameBase() {
            return GameBase::get();
        };
        Game& getGame() {
            return Game::get();
        };
    };
}

#endif //GAMESYSTEM_H
