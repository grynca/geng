#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

namespace grynca {

    class MovementSystem : public GengSystemAll {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erTransformMask() | GERoles::erSpeedMask();
        }

        virtual void update(f32 dt, EntitiesList& entities) override {
            entities.loopEntities([this, dt](Entity& e) {
                CTransformData* tr = e.getData<CTransformData>();
                CSpeedData* spd = e.getData<CSpeedData>();

                if (spd->isRotating()) {
                    tr->rotate(spd->getAngularSpeed() * dt);
                    e.setFlag(GEFlags::fEntityRotatedId);
                }
                if (spd->isMoving()) {
                    tr->move(spd->getLinearSpeed() * dt);
                    e.setFlag(GEFlags::fEntityMovedId);
                }
            });
        }
    };
}

#endif //MOVEMENTSYSTEM_H
