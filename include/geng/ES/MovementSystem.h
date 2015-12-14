#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

namespace grynca {

    template <typename GameType>
    class MovementSystem : public GameSystem<GameType> {
    public:
        void update(typename GameType::GameEntity&e, float dt) {
            EMovable& m = e.template getBase<EMovable>();
            Speed& s = m.getSpeed();
            m.move(s.getLinearSpeed()*dt);
            m.rotate(s.getAngularSpeed()*dt);
        }

        virtual RolesMask getNeededRoles() {
            return {GengEntityRoles::erMovable};
        }


    };
}

#endif //MOVEMENTSYSTEM_H
