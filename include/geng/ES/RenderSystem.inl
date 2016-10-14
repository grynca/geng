#include "RenderSystem.h"
#include "CRenderables.h"
#include "CTransform.h"
#include "../graphics/Renderables.h"

namespace grynca {

    template <typename GameType>
    inline void RenderSystem<GameType>::init() {
        window_ = &this->getGame().template getModule<Window>();
    }

    template <typename GameType>
    inline void RenderSystem<GameType>::preUpdate() {
        window_->getRenderer().clear();
        //float lag = std::min(this->getGame().getLag(), 1.0f);
        float lag = this->getGame().getLag();
        pred_time_ = lag*this->getGame().getTargetTicklen();
    }

    template <typename GameType>
    inline void RenderSystem<GameType>::updateEntity(Entity& e, float dt) {
        CRenderables& cr = e.getComponent<CRenderables>();
        CTransform& ct = e.getComponent<CTransform>();

        if (e.hasRoles({GengEntityRoles::erMovable})) {
            CMovable& cm = e.getComponent<CMovable>();
            Vec2 prev_pos = ct.get().getPosition();
            Angle prev_rot = ct.get().getRotation();
            // apply prediction
            ct.get().move(cm.getSpeed().getLinearSpeed()*pred_time_);
            ct.get().rotate(cm.getSpeed().getAngularSpeed()*pred_time_);
            ct.accMatrix() = ct.get().calcMatrix();

            renderEntity_(cr, ct, dt);

            // retract prediction
            ct.get().setPosition(prev_pos);
            ct.get().setRotation(prev_rot);
            ct.accMatrix() = ct.get().calcMatrix();
        }
        else {
            renderEntity_(cr, ct, dt);
        }
    }

    template <typename GameType>
    inline void RenderSystem<GameType>::renderEntity_(CRenderables& cr, CTransform& ct, float dt) {
        Renderables& rs = cr.accRenderables();
        ViewPort& vp = window_->getViewPort();
        for (uint32_t i=0; i<rs.size(); ++i) {
            RenderableBase& r = rs[i].getBase<RenderableBase>();
            if (!r.getVisible()) {
                continue;
            }

            if (rs[i].is<SpriteRenderable>()) {
                SpriteRenderable& sr = rs[i].get<SpriteRenderable>();
                if (sr.isAnimation() && !sr.isPaused())
                    sr.advanceAnimation(dt);
            }

            Renderer2D::RenderTask& rt = window_->getRenderer().addRenderTask(rs[i]);
            rt.mvp = vp.getProjectionTransform();

            switch (r.getCoordFrame()) {
                case cfScreen:
                    // translate 0,0 to left-top corner from center
                    rt.mvp *= Mat3::createTranslationT(-0.5f*vp.getBaseSize());
                    break;
                case cfWorld:
                    rt.mvp *= vp.getViewTransform();
                    break;
            }

            rt.mvp *= ct.accMatrix()
                      * r.accLocalTransform().calcMatrix();
        }
    }
}