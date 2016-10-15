#ifndef CRENDERABLES_H
#define CRENDERABLES_H

#include "../Renderables.h"

namespace grynca {

    class CRenderables {
    public:
        static RolesMask componentRoles() {
            return {GengEntityRoles::erRenderable};
        }

        const Renderables& getRenderables() { return renderables_; }
        Renderables& accRenderables() { return renderables_; }

        template <typename RenderableType>
        RenderableType& addRenderable(uint32_t& renderable_id_out) {
            renderable_id_out = renderables_.size();
            renderables_.push_back();
            return renderables_.back().set<RenderableType>();
        }

        template <typename RenderableType>
        RenderableType& addRenderable() {
            renderables_.push_back();
            return renderables_.back().set<RenderableType>();
        }

    private:
        Renderables renderables_;
    };

}

#endif //CRENDERABLES_H
