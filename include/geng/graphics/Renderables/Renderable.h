#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Renderer2D.h"

namespace grynca {

    // fw
    class Window;
    class Geom;
    class RenderTask;

    // common renderable
    class Renderable {
    public:
        struct DrawData {
            Mat3 transform;
            f32 z_coord;
        };
    public:
        Renderable();

        // creates new render task in Renderer2D
        template <typename RenderableType>
        void init();
        // reuses existing render task (e.g. changing renderable type)
        template <typename RenderableType>
        void init(Renderer2D::IPtr& render_task_ptr);
        // creates new render task with same shared geom & cloned DrawData
        void clone(const Renderer2D::IPtr& render_task);

        void setLayer(u16 layer_id);
        // reuses some other existing geom
        void setGeom(const Geom& geom);

        void setRenderTaskPtr(const Renderer2D::IPtr& render_task_ptr);

        const Renderer2D::IPtr& getRenderTaskPtr()const;
        Renderer2D::IPtr& accRenderTaskPtr();
        Index getRenderTaskId()const;
        bool getRenderBatchIdDirty()const;
        static Window& accWindow();
    protected:
        Renderer2D::IPtr render_task_ptr_;
        mutable bool render_batch_id_dirty_;
    };


    // convenience wrapper for less typing
    // creates new render task in Renderer2D
    template <typename RenderableType>
    static RenderableType createRenderable();
}

#include "Renderable.inl"
#endif //RENDERABLE_H
