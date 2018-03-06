#include "RenderSystem.h"
#include "geng/graphics/Components/CRenderable.h"
#include "geng/core/Components/CTransform.h"
#include "geng/core/Components/CSpeed.h"

namespace grynca {
    
    inline void RenderSystem::init() {
        window_ = &getGame().accWindow();
    }

    inline void RenderSystem::update(f32 dt, EntitiesList& entities) {
        f32 lag = this->getGame().getLag();
        pred_time_ = lag*this->getGame().getTargetTicklen();
        entities.loopEntities([this](Entity& e) {
            CRenderableData* crd = e.getData<CRenderableData>();
            Transform tr = *e.getData<CTransformData>();

            if (e.getRoles()[GERoles::erSpeedId]) {
                // TODO: motion prediction for TreeTransform children ?
                // apply motion prediction
                CSpeedData* csp = e.getData<CSpeedData>();
                if (!csp->isZero()) {
                    tr.move(csp->getLinearSpeed()*pred_time_);
                    tr.rotate(csp->getAngularSpeed()*pred_time_);
                }
            }

            Mat3 trm = (crd->getScreenFrame())
                            ?window_->getViewPort().calcScreenLocalTr(tr.calcMatrix(), crd->local_transform.calcMatrix())
                            :window_->getViewPort().calcWorldLocalTr(tr.calcMatrix(), crd->local_transform.calcMatrix());

            // schedule render task to renderer
            RenderTask& rt = window_->getRenderer().accItem(crd->render_task_id);
            window_->getRenderer().scheduleForNextFrame(rt.getId(), trm, crd->render_batch_id);
        });

        window_->render(dt);
    }
}