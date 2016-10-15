#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "SAP.h"
#include "../../core/GengSystem.h"
#include "../../core/GengEntityRoles.h"
#include "../../core/GengEntityFlags.h"

namespace grynca {

    template <typename GameType>
    class CollisionSystem : public GengSystem<GameType> {
    public:
        virtual FlagsMask getTrackedFlags() override {
            return {GengEntityFlags::fMoved, GengEntityFlags::fRotated, GengEntityFlags::fScaled};
        };

        virtual RolesMask getNeededRoles() override {
            return {GengEntityRoles::erCollidable, GengEntityRoles::erTransform };
        }

        virtual void afterAddedEntity(Entity& e) override;
        virtual void beforeRemovedEntity(Entity& e) override;

        virtual void postUpdate() override;
        virtual void updateEntity(Entity& e, float dt) override;

        SAPManager<EntityIndex, 2>& getSAP() { return sap_; };
    private:
        SAPManager<EntityIndex, 2> sap_;
    };
}
#include "CollisionSystem.inl"
#endif //COLLISIONSYSTEM_H
