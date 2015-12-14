#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "../Game.h"

namespace grynca {

    template <typename GameType>
    class GameSystem {
    public:
        typedef typename GameType::BaseType GameBaseType;

        GameType& getGame() { return GameType::get(); }

        GameBaseType& getGameBase() {
            return *(GameBaseType*)GameType::getptr();
        };


        void init() {}

        void preUpdate() {}
        void postUpdate() {}
    };

}

#endif //GAMESYSTEM_H
