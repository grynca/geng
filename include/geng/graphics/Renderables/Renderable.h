#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Renderer2D.h"

namespace grynca {

    // fw
    class Window;
    class Geom;
    class RenderTask;

    // common renderable setter
    class Renderable {
    public:

        // with new geom
        template <typename RenderableType>
        static RenderableType create();
        template <typename RenderableType>
        static RenderableType create(GeomState::UsageHint usage_hint);

        // reuses geom
        template <typename RenderableType>
        static RenderableType create(const VertexData::ItemRef& geom);

        const Renderer2D::ItemRef& getRenderTask()const;
        Index getRenderTaskId()const;
        Window& getWindow()const;

        Renderer2D::ItemRef& accRenderTask();
    protected:
        Renderable(const Renderer2D::ItemRef& rt);

        Renderer2D::ItemRef render_task_;
    };
}

#include "Renderable.inl"
#endif //RENDERABLE_H
