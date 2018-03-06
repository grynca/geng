#ifndef VERTICES_H
#define VERTICES_H

#include "types/Manager.h"

namespace grynca {

    // fw
    class Window;
    class VertexData;

    class Vertices : public ManagerSingletons<VertexData> {
    public:
        Vertices(Window& w);

        void update(f32 dt);

        Window& getWindow();
        std::string getTypesDebugString()const;
        std::string getDebugString(u32 indent_cnt)const;
    private:
        friend class VertexData;

        Window* window_;
    };

}

#include "Vertices.inl"
#endif //VERTICES_H