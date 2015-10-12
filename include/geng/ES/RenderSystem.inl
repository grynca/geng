#include "RenderSystem.h"
#include "ERenderables.h"
#include "ENonMovable.h"
#include "../graphics/Renderables/SpriteRenderable.h"
#include "../graphics/Window.h"

namespace grynca {

    template <typename GameType>
    inline void RenderSystem::init(GameType& game) {
        window_ = &game.template getModule<Window>();
    }

    inline void RenderSystem::preUpdate() {
        window_->getRenderer().clear();
    }

    template <typename ES>
    inline void RenderSystem::update(Entity<ES>& e, float dt) {
        Renderables& rs = e.template getBase<ERenderables>().getRenderables();
        Transform& t = e.template getBase<ENonMovable>().getTransform();
        ViewPort& vp = window_->getViewPort();
        for (uint32_t i=0; i<rs.getSize(); ++i) {
            Renderable* r = (Renderable*)rs.get(i);

            if (rs.getTypeId(i) == GraphicsDomain::getTypeId<SpriteRenderable>()) {
                SpriteRenderable* sr = (SpriteRenderable*)r;
                if (sr && !sr->isPaused())
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
            mvp *= t.getTransform()
                   *r->getLocalTransform().getTransform();

            r->setMVP(mvp);
            window_->getRenderer().addRenderable(r);
        }
    }
}