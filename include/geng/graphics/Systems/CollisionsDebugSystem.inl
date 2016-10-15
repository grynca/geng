#include <geng.h>
#include "CollisionsDebugSystem.h"
#include "../../physics/Systems/CollisionSystem.h"
#include "../Window.h"

#define CDS_TPL template <typename GameType>
#define CDS_TYPE CollisionsDebugSystem<GameType>

#define CDS_LAYERID 200

namespace grynca {

    CDS_TPL
    inline void CDS_TYPE::init() {
        GameType& g =  this->getGame();
        window_ = &g.template getModule<Window>();
        cs_ = g.template findUpdateSystem<CollisionSystem<GameType> >();
        rend_.set<RectBorderRenderable>()
                .init(g)
                .setColor(Colorf::Green())
                .setBorders({2, 2})
                .setGeomNormOffset({0, 0});
        ASSERT(cs_ && "CollisionSystem not found.")
    }

    CDS_TPL
    inline void CDS_TYPE::updateEntity(Entity& e, float dt) {
        CBody& cb = e.getComponent<CBody>();
        if (cb.getSapId() == InvalidId())
            return;

        ViewPort& vp = window_->getViewPort();
        CTransform& ct = e.getComponent<CTransform>();

        ARect bound;
        cs_->getSAP().getBox(cb.getSapId(), bound.getDataPtr());
        RectBorderRenderable& r = rend_.get<RectBorderRenderable>();
        r.setLayerId(CDS_LAYERID);
        r.setSize(bound.getSize());
        r.accLocalTransform().setPosition(bound.getLeftTop());

        Renderer2D::RenderTask& rt = window_->getRenderer().addRenderTask(rend_);
        rt.mvp = vp.getProjectionTransform()*vp.getViewTransform()* r.accLocalTransform().calcMatrix();
    }

}

#undef CDS_TPL
#undef CDS_TYPE