#include "RenderSystem.h"
#include "../Window.h"
#include "../Renderer2D.h"
#include "types/Call.h"

namespace grynca {

    template <typename T>
    inline void RenderSystem::UpdatePos::f(T& e, Window& window) {
        // static
        ViewPort& vp = window.getViewPort();
        for (uint32_t i=0; i<e.renderables.getSize(); ++i) {
            Renderable* r = (Renderable*)e.renderables.get(i);
            Mat3 mvp = vp.getProjectionTransform();

            switch (r->getFrame()) {
                case fScreen:
                    // translate 0,0 to left-top corner from center
                    mvp *= Mat3::createTranslationT(-0.5f*vp.getBaseSize());
                    break;
                case fWorld:
                    mvp *= vp.getViewTransform();
                    break;
            }
            mvp *= e.transform.getTransform()
                   *r->getLocalTransform().getTransform();
            r->setMVP(mvp);
            window.getRenderer().addRenderable(r);
        }
    }

    inline void RenderSystem::init(Window& window) {
        window_ = &window;
    }

    template <typename T>
    inline void RenderSystem::update(Entity& e, T& t, double /*dt*/) {
        Call<UpdatePos>::ifTrue<HasProps<T, props::has_renderables, props::has_transform> > (t, *window_);
    }

    inline RolesMask RenderSystem::getNeededRoles() {
        return {erRenderable};
    }

}