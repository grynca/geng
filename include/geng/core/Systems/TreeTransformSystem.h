#ifndef TREETRANSFORMSYSTEM_H
#define TREETRANSFORMSYSTEM_H

namespace grynca {

    class TreeTransformSystem : public GengSystemScheduled {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erTreeTransformMask();
        }

        virtual void init() override;
        void recieve(EntityFlagCtx& efctx);
        virtual void update(f32 dt, EntitiesList& entities) override;

        void checkMaxDepth(u32 depth);
    private:
        void scheduleGlTransformUpdateRec_(EntityManager &emgr, EntityIndex eid);

        // first index is depth
        FAST_VECTOR_2D(Entity) scheduled_global_tr_update_;
        fast_vector<Entity> scheduled_local_tr_update_;
    };
}
#endif //TREETRANSFORMSYSTEM_H

#if !defined(TREETRANSFORMSYSTEM_INL) && !defined(WITHOUT_IMPL)
#   define TREETRANSFORMSYSTEM_INL
#   include "TreeTransformSystem.inl"
#endif // TREETRANSFORMSYSTEM_INL

