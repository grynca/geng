#ifndef RENDERER_H
#define RENDERER_H

#include "graphics_config.h"
#include "types/containers/fast_vector.h"
#include <stdint.h>

namespace grynca {
    // fw
    class Window;
    class Renderable;

    class Renderer2D {
    public:
        Renderer2D(Window& w);

        void addRenderable(Renderable* r);
        void render();
        void clear();
    private:
        Window* window_;

        fast_vector<Renderable*> renderables_;
    };

}


#include "Renderer2D.inl"
#endif //RENDERER_H
