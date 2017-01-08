#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

namespace grynca {

    class MovementSystem : public GengSystem {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erTransformMask() | GERoles::erMovableMask();
        }

        virtual void updateEntity(Entity& e, f32 dt) override {
            CTransform& ct = e.getComponent<CTransform>();
            Transform& t = ct.acc_();
            Speed& s = e.getComponent<CMovable>().getSpeed();
            bool rot_scaled = false;
            if (s.hasLinearSpeed()) {
                t.move(s.getLinearSpeed() * dt);
                e.setFlag(GEFlags::fMovedId);
            }
            if (s.hasAngularSpeed()) {
                t.rotate(s.getAngularSpeed()*dt);
                rot_scaled = true;
            }
            if (s.hasScalarSpeed()) {
                t.scale(s.getScalarSpeed()*dt);
                rot_scaled = true;
            }

            if (rot_scaled) {
                e.setFlag(GEFlags::fRotScaledId);
            }
        }
    };
}

#endif //MOVEMENTSYSTEM_H
