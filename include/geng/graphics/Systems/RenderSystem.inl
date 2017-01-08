#include "RenderSystem.h"
#include "../Components/CRenderables.h"
#include "../../core/Components/CTransform.h"

namespace grynca {
    
    inline void RenderSystem::init() {
        window_ = &this->getGame().template getModule<Window>();
    }

    inline void RenderSystem::preUpdate(f32 dt) {
        f32 lag = this->getGame().getLag();
        pred_time_ = lag*this->getGame().getTargetTicklen();
    }

    inline void RenderSystem::updateEntity(Entity& e, f32 dt) {
        CRenderables& cr = e.getComponent<CRenderables>();
        CTransform& ct = e.getComponent<CTransform>();

        if (e.getRoles()[GERoles::erMovableId]) {
            CMovable& cm = e.getComponent<CMovable>();
            Vec2 prev_pos = ct.get().getPosition();
            Angle prev_rot = ct.get().getRotation();
            // apply prediction
            ct.acc_().move(cm.getSpeed().getLinearSpeed()*pred_time_);
            ct.acc_().rotate(cm.getSpeed().getAngularSpeed()*pred_time_);

            renderEntity_(cr, ct);

            // retract prediction
            ct.acc_().setPosition(prev_pos);
            ct.acc_().setRotation(prev_rot);
        }
        else {
            renderEntity_(cr, ct);
        }
    }

    inline void RenderSystem::postUpdate(f32 dt) {
        window_->render(dt);
    }

    inline void RenderSystem::renderEntity_(CRenderables& cr, CTransform& ct) {
        Mat3 ent_m = ct.get().calcMatrix();
        for (u32 i=0; i<cr.renderables_.size(); ++i) {
            RenderTask& rt = cr.accRenderTask(i).get();
            rt.calcTransform(*window_, ent_m);
            window_->getRenderer().scheduleForNextFrame(rt.getId());
        }
    }
}