#ifndef CRENDERABLES_H
#define CRENDERABLES_H

#include "../Renderables/Renderable.h"

namespace grynca {

    class CRenderables {
    public:
        static RolesMask componentRoles() {
            return GERoles::erRenderableMask();
        }

        u32 getRenderablesSize()const {
            return u32(renderables_.size());
        }

        // creates new geom
        template <typename RenderableType>
        RenderableType addRenderable(GeomState::UsageHint usage_type) {
            RenderableType r = Renderable::create<RenderableType>(usage_type);
            renderables_.push_back(r.accRenderTask());
            return r;
        }

        // creates new geom
        template <typename RenderableType>
        RenderableType addRenderable() {
            RenderableType r = Renderable::create<RenderableType>();
            renderables_.push_back(r.accRenderTask());
            return r;
        }

        // reuses geom
        template <typename RenderableType>
        RenderableType addRenderable(Geom& geom) {
            RenderableType r = Renderable::create<RenderableType>(geom);
            renderables_.push_back(r.accRenderTask());
            return r;
        }

        template <typename RenderableType = Renderable>
        RenderableType getRenderable(u32 rend_id) {
            return RenderableType(renderables_[rend_id]);
        }

        Renderer2D::ItemRef& accRenderTask(u32 r_id) {
            return renderables_[r_id];
        }

    private:
        friend class RenderSystem;

        fast_vector<Renderer2D::ItemRef> renderables_;
    };
}

#endif //CRENDERABLES_H
