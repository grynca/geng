#include "Renderer2D.h"

namespace grynca {

    inline bool Renderer2D::RenderTask::compare(RenderTask& r1, RenderTask& r2){
        //static
        return RenderableBase::compare(&r1.renderable->getBase<RenderableBase>(), &r2.renderable->getBase<RenderableBase>());
    }

    inline Renderer2D::Renderer2D(Window& w)
     : window_(&w)
    {
    }

    inline Renderer2D::RenderTask& Renderer2D::addRenderTask(Renderable& r) {
        render_tasks_.push_back();
        render_tasks_.back().renderable = &r;
        return render_tasks_.back();
    }

    inline void Renderer2D::render() {
        std::sort(render_tasks_.begin(), render_tasks_.end(), RenderTask::compare);
        for (uint32_t i=0; i<render_tasks_.size(); ++i) {
            RenderableBase& r = render_tasks_[i].renderable->getBase<RenderableBase>();
            Shader& s = r.getShaderInner(*window_);
            s.bind();
            r.setUniforms(render_tasks_[i].mvp, s);
            r.getVertexDataInner(*window_).bind();
            r.render();
        }
    }

    inline void Renderer2D::clear() {
        render_tasks_.clear();
    }
}
