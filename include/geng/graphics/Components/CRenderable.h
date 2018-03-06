#ifndef CRENDERABLES_H
#define CRENDERABLES_H

#include "../Renderables/renderables_includes.h"

namespace grynca {

    class CRenderableData {
    public:
        static RolesMask componentRoles() {
            return GERoles::erRenderableMask();
        }

        // elements in screen frame (e.g. HUD), packed to r.t. index for better data align
        bool getScreenFrame()const { return render_task_id.getAuxIndex()==0; }
        void setScreenFrame(bool val) { render_task_id.setAuxIndex(u16(!val)); }

        Transform local_transform;
        RenderBatchId render_batch_id;      // cached render batch id for RenderTask
        Index render_task_id;       // TODO: removing render tasks ?
    };

    // TODO: polish a little

    class CRenderable : public EntityAccessor<CRenderableData> {
        typedef EntityAccessor<CRenderableData> Base;
    public:
        MOVE_ONLY(CRenderable);
        CRenderable();
        ~CRenderable();

        template <typename RenderableType>
        RenderableType* initR();

        template <typename RenderableType>
        RenderableType* initRCloned(const Renderer2D::IPtr& render_task);

        // for changing type (but already initialized before)
        template <typename RenderableType>
        RenderableType* changeR();

        template <typename RenderableType = Renderable>
        const RenderableType* getR();

        template <typename RenderableType = Renderable>
        RenderableType* accR();

        void setScreenFrame(bool val);
        void setLocalTransform(const Transform& tr);

        const Transform& getLocalTransform()const;
        Index getRenderTaskId()const;
        bool getScreenFrame()const;
        Transform& accLocalTransform();
    private:
        Renderer2D& getRendererSingleton_();

        Variant<RenderableTypes> renderable_;
        bool dirty_;
    };
}

#include "CRenderable.inl"
#endif //CRENDERABLES_H
