#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "SAP.h"
#include "../../core/GengSystem.h"
#include "geng/GERoles.h"
#include "geng/GEFlags.h"

namespace grynca {

    class CollisionSystem : public GengFlaggedSystem{
    public:

        virtual RolesMask NeededRoles() override {
            return GERoles::erCollidableMask() | GERoles::erTransformMask();
        }

        virtual FlagsMask NeededFlags() override {
            return GEFlags::fMovedMask() | GEFlags::fRotScaledMask();
        }

        virtual void afterAddedEntity(Entity& e) override;
        virtual void beforeRemovedEntity(Entity& e) override;

        virtual void postUpdate(f32 dt) override;
        virtual void updateEntity(Entity& e, f32 dt) override;

        SAPManager<EntityIndex, 2>& getSAP() { return sap_; };
    private:
        SAPManager<EntityIndex, 2> sap_;
    };
}
#include "CollisionSystem.inl"
#endif //COLLISIONSYSTEM_H
