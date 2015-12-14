#include "RenderSystem.h"
#include "ERenderables.h"
#include "ETransform.h"
#include "../graphics/Renderables/SpriteRenderable.h"
#include "../graphics/Window.h"

namespace grynca {

    template <typename GameType>
    inline void RenderSystem<GameType>::init() {
        window_ = &this->getGame().template getModule<Window>();
    }

    template <typename GameType>
    inline void RenderSystem<GameType>::preUpdate() {
        window_->getRenderer().clear();
    }

    template <typename GameType>
    inline void RenderSystem<GameType>::update(typename GameType::GameEntity& e, float dt) {
        Renderables& rs = e.template getBase<ERenderables>().getRenderables();
        const Transform& t = e.template getBase<ETransform>().getTransform();
        ViewPort& vp = window_->getViewPort();
        for (uint32_t i=0; i<rs.getSize(); ++i) {
            Renderable* r = (Renderable*)rs.get(i);

            if (rs.getTypeId(i) == GraphicsDomain::getTypeId<SpriteRenderable>()) {
                SpriteRenderable* sr = (SpriteRenderable*)r;
                if (sr && sr->isAnimation() && !sr->isPaused())
                    sr->advanceAnimation(dt);
            }


            Mat3 mvp = vp.getProjectionTransform();

            switch (r->getCoordFrame()) {
                case cfScreen:
                    // translate 0,0 to left-top corner from center
                    mvp *= Mat3::createTranslationT(-0.5f*vp.getBaseSize());
                    break;
                case cfWorld:
                    mvp *= vp.getViewTransform();
                    break;
            }
            mvp *= t.getMatrix()
                   *r->getLocalTransform().getMatrix();

            r->setMVP(mvp);
            window_->getRenderer().addRenderable(r);
        }
    }
}