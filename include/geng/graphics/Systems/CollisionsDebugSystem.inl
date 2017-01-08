#include "CollisionsDebugSystem.h"
#include "../../physics/Systems/CollisionSystem.h"
#include "../Renderables/RectBorderRenderable.h"

#define CDS_LAYERID u16(200)

namespace grynca {

    inline void CollisionsDebugSystem::init() {
        window_ = &getGame().getWindow();
        cs_ = getGameBase().findUpdateSystem<CollisionSystem>();
        ASSERT(cs_ && "CollisionSystem not found.");

        Geom& shared_geom = window_->getVertices().get<VertexDataP>().getSharedQuadLT().get();
        RectBorderRenderable r = Renderable::create<RectBorderRenderable>(shared_geom);
        r.setColor(Colorf::Green()).setBorders({2, 2});
        r.accRenderTask()->setLayer(CDS_LAYERID);
        rt_ = r.accRenderTask();
    }

    inline void CollisionsDebugSystem::updateEntity(Entity& e, f32 dt) {
        CBody& cb = e.getComponent<CBody>();
        if (cb.getSapId() == InvalidId())
            return;

        ViewPort& vp = window_->getViewPort();
        ARect bound;
        cs_->getSAP().getBox(cb.getSapId(), bound.getDataPtr());
        RectBorderRenderable r(rt_);
        RenderTask& rt = r.accRenderTask().get();
        rt.accLocalTransform().setPosition(bound.getLeftTop());
        r.setSize(bound.getSize());


        window_->getRenderer().scheduleForNextFrame(r.getRenderTaskId());
        rt.setTransformMatrix(vp.getProjectionTransform()*vp.getViewTransform()* rt.accLocalTransform().calcMatrix());
    }

}