
#ifndef ENDTICKSYSTEM_H
#define ENDTICKSYSTEM_H

namespace grynca {

    template <typename GameType>
    class StartTickSystem : public GameSystem<GameType> {
    public:
        void update(typename GameType::GameEntity &e, float dt) {
            GengEntity& ge = e.template getBase<GengEntity>();
            ge.getFlags().reset();
        }

        virtual RolesMask getNeededRoles() {
            return {};
        }
    };
}


#endif //ENDTICKSYSTEM_H
