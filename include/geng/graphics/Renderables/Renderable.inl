#include "Renderable.h"
#include "../../Game.h"
#include "../Window.h"

namespace grynca {

    template <typename RT>
    inline RT Renderable::create() {
        // static
        return create<RT>(RT::createNewGeom(Game::get().getWindow()));
    }

    template <typename RT>
    inline RT Renderable::create(GeomState::UsageHint usage_hint) {
        // static
        return create<RT>(RT::createNewGeom(Game::get().getWindow(), usage_hint));
    }

    template <typename RT>
    inline RT Renderable::create(const VertexData::ItemRef& geom) {
        // static
        Window& w = Game::get().getWindow();
        Renderer2D& renderer = w.getRenderer();
        RenderTask& rt =  renderer.addItem();
        RenderIndex& rid = rt.accRenderIndex();
        rid.setShaderId(u16(w.getShaders().get<typename RT::ShaderType>().getId()));
        rid.setVertexLayoutId(u16(w.getVertices().get<typename RT::VertexDataType>().getId()));
        rid.setVertexBufferId(u16(geom->getVertexBufferId()));
        rt.setGeom(geom);
        return RT(rt);
    }

    inline Renderable::Renderable(const Renderer2D::ItemRef& rt)
     : render_task_(rt)
    {
    }

    inline const Renderer2D::ItemRef& Renderable::getRenderTask()const {
        return render_task_;
    }

    inline Index Renderable::getRenderTaskId()const {
        return render_task_.getItemId();
    }

    inline Window& Renderable::getWindow()const {
        return render_task_.getManager().getWindow();
    }

    inline Renderer2D::ItemRef& Renderable::accRenderTask() {
        return render_task_;
    }
}