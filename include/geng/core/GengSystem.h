#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "../GameBase.h"

namespace grynca {

    template <typename GameType>
    class GengSystem : public SystemBase {
        using GameBaseType = GameBase<typename GameType::DerivedType>;
    public:
        GameType& getGame() { return GameType::get(); }

        GameBaseType& getGameBase() {
            return *(GameBaseType*)GameType::getptr();
        };
    };

}

#endif //GAMESYSTEM_H
