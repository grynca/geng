#include "Renderer2D.h"
#include "Renderable.h"
#include <algorithm>

namespace grynca {

    inline Renderer2D::Renderer2D(Window& w)
     : window_(&w)
    {
    }

    inline void Renderer2D::addRenderable(Renderable* r) {
        renderables_.push_back(r);
    }

    inline void Renderer2D::render() {
        std::sort(renderables_.begin(), renderables_.end(), Renderable::compare);
        for (uint32_t i=0; i<renderables_.size(); ++i) {
            renderables_[i]->render();
        }
    }

    inline void Renderer2D::clear() {
        renderables_.clear();
    }

}
