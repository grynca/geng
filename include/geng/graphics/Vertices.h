#ifndef VERTICES_H
#define VERTICES_H

#include "types/Manager.h"

namespace grynca {

    // fw
    class Window;
    class VertexData;

    class Vertices : public ManagerSingletons<Vertices, VertexData> {
    public:
        Vertices(Window& w);

        void syncWithGPU();

        VertexData* getBoundVertexData();
        Window& getWindow();
    private:
        friend class VertexData;

        Window* window_;
        uint32_t bound_id_;
    };

}

#include "Vertices.inl"
#endif //VERTICES_H
