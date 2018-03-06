#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "geng/physics/PhysicsManager.h"

namespace grynca {

    class PhysicsSystem : public GengSystemAll {
    public:
        virtual void init() override {
            ph_mgr_ = &getGame().accPhysicsManager();
        }

        virtual RolesMask NeededRoles() override {
            return GERoles::erTransformMask() | GERoles::erSpeedMask() | GERoles::erBodyMask();
        }

        virtual void update(f32 dt, EntitiesList& entities) override {
            // force -> tentative speed
            entities.loopEntities([this, dt](Entity& e) {
                CBodyData* cbd = e.getData<CBodyData>();
                CSpeedData* csd = e.getData<CSpeedData>();

                ph_mgr_->updateVelocity(*cbd, *csd);
            });

            // loop through SAP contacts & call near callbacks
            ph_mgr_->updateContacts();

            // solve velocities
            ph_mgr_->solve();

            // zero out small speeds
            entities.loopEntities([this, dt](Entity& e) {
                CSpeedData* csd = e.getData<CSpeedData>();
                Vec2& ls = csd->accLinearSpeed();
                Angle& as = csd->accAngularSpeed();

                if (fabsf(ls.getX()) < maths::EPS && fabsf(ls.getY()) < maths::EPS) {
                    // zero out small speeds
                    ls.set(0.0f, 0.0f);
                    csd->accFlags() = CLEAR_BIT(csd->getFlags(), CSpeedData::fMoving);
                }
                else {
                    csd->accFlags() = SET_BIT(csd->getFlags(), CSpeedData::fMoving);
                }

                if (fabsf(as) < maths::EPS) {
                    // zero out small speeds
                    as = 0.0f;
                    csd->accFlags() = CLEAR_BIT(csd->getFlags(), CSpeedData::fRotating);
                }
                else {
                    csd->accFlags() = SET_BIT(csd->getFlags(), CSpeedData::fRotating);
                }
            });
        }
    private:
        PhysicsManager* ph_mgr_;
    };

}

#endif //PHYSICSSYSTEM_H
