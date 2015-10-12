#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

namespace grynca {

    class MovementSystem : public GameSystem {
    public:
        template <typename ES>
        void update(Entity<ES> &e, float dt) {
            EMovable& m = e.template getBase<EMovable>();
            Transform& t = m.getTransform();
            Speed& s = m.getSpeed();
            t.setPosition(t.getPosition()+s.getLinearSpeed()*dt);
            t.setRotation(t.getRotation()+s.getAngularSpeed()*dt);
        }

        virtual RolesMask getNeededRoles() {
            return {GengEntityRoles::erMovable};
        }


    };
}

#endif //MOVEMENTSYSTEM_H
