#include "Renderable.h"
#include "../../GameBase.h"
#include "../Window.h"

namespace grynca {

    inline Renderable::Renderable()
     : render_batch_id_dirty_(false)
    {
    }

    template <typename RT>
    inline void Renderable::init() {
        render_batch_id_dirty_ = true;
        render_task_ptr_ = accWindow().getRenderer().addItem();
        render_task_ptr_->setRenderableTypeId(Renderer2D::getRenderableTypeIdOf<RT>());

        // default-construct draw data
        typename RT::DrawData& dd = render_task_ptr_->accDrawDataAs<typename RT::DrawData>();
        new (&dd) typename RT::DrawData();
    }

    template <typename RT>
    inline void Renderable::init(Renderer2D::IPtr& render_task_ptr) {
        render_batch_id_dirty_ = true;
        render_task_ptr_ = render_task_ptr;
        render_task_ptr_->setRenderableTypeId(Renderer2D::getRenderableTypeIdOf<RT>());

        // default-construct draw data
        typename RT::DrawData& dd = render_task_ptr_->accDrawDataAs<typename RT::DrawData>();
        new (&dd) typename RT::DrawData();
    }

    inline void Renderable::clone(const Renderer2D::IPtr& render_task) {
        render_batch_id_dirty_ = true;
        RenderTask& new_render_task = render_task.getContainer().addItem();
        render_task->cloneTo(new_render_task);
        render_task_ptr_ = new_render_task;
    }

    inline void Renderable::setLayer(u16 layer_id) {
        render_task_ptr_->setZFromLayerId(layer_id);
        render_batch_id_dirty_ = true;
    }

    inline void Renderable::setGeom(const Geom& geom) {
        render_task_ptr_->setGeom(geom);
        render_batch_id_dirty_ = true;
    }

    inline void Renderable::setRenderTaskPtr(const Renderer2D::IPtr& render_task_ptr) {
        render_task_ptr_ = render_task_ptr;
    }

    inline const Renderer2D::IPtr& Renderable::getRenderTaskPtr()const {
        return render_task_ptr_;
    }

    inline Renderer2D::IPtr& Renderable::accRenderTaskPtr() {
        return render_task_ptr_;
    }

    inline Index Renderable::getRenderTaskId()const {
        return render_task_ptr_.getItemId();
    }

    inline bool Renderable::getRenderBatchIdDirty()const {
        return render_batch_id_dirty_;
    }

    inline Window& Renderable::accWindow() {
        // static
        return GameBase::get().accModule<Window>();
    }

    template <typename RenderableType>
    inline RenderableType createRenderable() {
        // static
        RenderableType rslt;
        rslt.template init<RenderableType>();
        return rslt;
    }
}