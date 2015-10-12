#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

namespace grynca {

    class GameSystem {
    public:
        template <typename GameType>
        void init(GameType& game) {}
        void preUpdate() {}
        void postUpdate() {}
    };

}

#endif //GAMESYSTEM_H
