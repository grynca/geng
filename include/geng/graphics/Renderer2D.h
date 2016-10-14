#ifndef RENDERER_H
#define RENDERER_H

#include "Renderables.h"

namespace grynca {
    // fw
    class Window;
    class RenderableBase;

    class Renderer2D {
    public:
        struct RenderTask {
            Renderable* renderable;
            Mat3 mvp;

            static bool compare(RenderTask& r1, RenderTask& r2);
        };

        Renderer2D(Window& w);

        RenderTask& addRenderTask(Renderable& rv);
        void render();
        void clear();
    private:

        Window* window_;
        fast_vector<RenderTask> render_tasks_;
    };

}


#include "Renderer2D.inl"
#endif //RENDERER_H
