#ifndef UPDATEBOUNDSSYSTEM_H
#define UPDATEBOUNDSSYSTEM_H

namespace grynca {

    class BoundsSystem : public GengSystemScheduled {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erTransformMask() | GERoles::erColliderMask();
        }

        virtual void init() override;
        void recieve(EntityFlagCtx& efctx);

        virtual void onEntityAdded(Entity &e, bool by_roles_change) override;
        virtual void onEntityRemoved(Entity &e, bool by_roles_change) override;
        virtual void update(f32 dt, EntitiesList& entities) override;
    private:
        PhysicsManager* pm_;
        FlagsMaskLong update_bound_fm_;
    };
}

#include "BoundsSystem.inl"
#endif //UPDATEBOUNDSSYSTEM_H
