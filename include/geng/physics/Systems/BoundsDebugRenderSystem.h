#ifndef COLLISIONSDEBUGSYSTEM_H
#define COLLISIONSDEBUGSYSTEM_H

namespace grynca {

    class BoundsDebugRenderSystem: public GengSystemAll {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erColliderMask() | GERoles::erTransformMask();
        }

        virtual void init() override;
        virtual void update(f32 dt, EntitiesList& entities) override;
    private:
        void addBoundRenderTask_(Index sap_bound_id);
        void addShapeRenderTask_(CTransformData* ctd, CColliderData* cco);
        template <typename RenderableType>
        RenderableType getShapeRenderable_(u32 shape_rt_id);

        Window* window_;
        PhysicsManager* ph_mgr_;
        fast_vector<Index> bound_render_tasks_;
        fast_vector<Index> shape_render_tasks_;

        u32 bound_rt_id_;
        u32 shape_rt_id_;
    };

}

#include "BoundsDebugRenderSystem.inl"
#endif //COLLISIONSDEBUGSYSTEM_H
