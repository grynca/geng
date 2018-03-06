#include "BoundsDebugRenderSystem.h"
#include "../../graphics/Renderables/RectBorderRenderable.h"
#include "../../graphics/Renderables/RectRenderable.h"
#include "../../graphics/Renderables/CircleRenderable.h"

#define TID(ST) Shape::getTypeIdOf<ST>()
#define BOUND_CLR {1.0f, 1.0f, 1.0f, 0.3f}
#define SHAPE_CLR {1.0f, 1.0f, 0.0f, 0.4f}

namespace grynca {

    inline void BoundsDebugRenderSystem::init() {
        window_ = &getGame().accWindow();
        ph_mgr_ = &getGame().accPhysicsManager();
    }

    inline void BoundsDebugRenderSystem::update(f32 dt, EntitiesList& entities) {
        bound_rt_id_ = 0;
        shape_rt_id_ = 0;

        entities.loopEntities([this](Entity& e) {
            CColliderData* cco = e.getData<CColliderData>();
            CTransformData* ctd = e.getData<CTransformData>();

            addBoundRenderTask_(cco->getSapId());
            addShapeRenderTask_(ctd, cco);
        });
    }

    inline void BoundsDebugRenderSystem::addBoundRenderTask_(Index sap_bound_id) {
        ARect* bound = (ARect*)ph_mgr_->accSAP().getBox(sap_bound_id).getBounds();

        RectBorderRenderable bound_rr;
        if (bound_rt_id_ >= bound_render_tasks_.size()) {
            bound_rr.init<RectBorderRenderable>();
            bound_rr.setColor(BOUND_CLR);
            bound_rr.setStaticSharedQuadGeom(NormOffset::otLeftTop);
            bound_rr.setBordersPx({2, 2});
            bound_rr.setLayer(config::MAX_LAYERS-3);
            bound_render_tasks_.push_back(bound_rr.getRenderTaskId());
        }
        else {
            bound_rr.setRenderTaskPtr(window_->getRenderer().accItem(bound_render_tasks_[bound_rt_id_]));
            bound_rr.setSize(bound->getSize());
        }

        Mat3 tr_mat = window_->getViewPort().calcWorldGlobalTr(Mat3::createTranslationT(bound->getLeftTop()));
        window_->getRenderer().scheduleForNextFrame(bound_rr.getRenderTaskId(), tr_mat);
        ++bound_rt_id_;
    }

    inline void BoundsDebugRenderSystem::addShapeRenderTask_(CTransformData* ctd, CColliderData* cco) {
        Mat3 local_trm;
        Renderable rend;

        switch (cco->getShape().getTypeId()) {
            case TID(Circle): {
                const Circle& circle = cco->getShape().get<Circle>();
                CircleRenderable cr = getShapeRenderable_<CircleRenderable>(shape_rt_id_);
                cr.setStaticSharedGeom();
                cr.setOuterRadius(circle.getRadius());
                local_trm = Mat3::createTranslationT(circle.getCenter());
                rend = cr;
            }break;
            case TID(ARect): {
                const ARect& arect = cco->getShape().get<ARect>();
                RectRenderable rr = getShapeRenderable_<RectRenderable>(shape_rt_id_);
                Vec2 norm_offset = arect.getLeftTop()/arect.getSize();
                rr.setNewGeom(norm_offset);
                rr.setSize(arect.getSize());
                rend = rr;
            }break;
            case TID(Rect): {
                const Rect& rect = cco->getShape().get<Rect>();
                RectRenderable rr = getShapeRenderable_<RectRenderable>(shape_rt_id_);
                Vec2 norm_offset = rect.getOffset()/rect.getSize();
                rr.setNewGeom(norm_offset);
                rr.setSize(rect.getSize());
                local_trm = Mat3::createTransform(rect.getPosition(), rect.getRotation());
                rend = rr;
            }break;
            case TID(Pgon): {
                //const Pgon& pgon = cco->getShape().get<Pgon>();
                // TODO:
                NEVER_GET_HERE("TODO: implement!");
            }break;
            default:
                NEVER_GET_HERE("NOT implemented.");
                return;
        }

        Mat3 tr_mat = window_->getViewPort().calcWorldLocalTr(ctd->calcMatrix(), local_trm);
        window_->getRenderer().scheduleForNextFrame(rend.getRenderTaskId(), tr_mat);

        ++shape_rt_id_;
    }

    template <typename RenderableType>
    inline RenderableType BoundsDebugRenderSystem::getShapeRenderable_(u32 shape_rt_id) {
        RenderableType rslt;
        if (shape_rt_id >= shape_render_tasks_.size()) {
            rslt.template init<RenderableType>();
            rslt.template setLayer(config::MAX_LAYERS - 4);
            rslt.template setColor(SHAPE_CLR);
            shape_render_tasks_.push_back(rslt.getRenderTaskId());
        }
        else {
            Renderer2D::IPtr render_task_ptr = window_->getRenderer().accItem(shape_render_tasks_[shape_rt_id]);
            rslt.template init<RenderableType>(render_task_ptr);
            rslt.template setLayer(config::MAX_LAYERS - 4);
            rslt.template setColor(SHAPE_CLR);;
        }
        return rslt;
    }

}

#undef TID
#undef BOUND_CLR
#undef SHAPE_CLR