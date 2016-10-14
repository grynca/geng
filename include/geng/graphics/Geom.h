#ifndef GEOM_H
#define GEOM_H

#include "types/Manager.h"
#include "glinclude.h"

namespace grynca {
    // fw
    class VertexData;

    class Geom : public ManagedItem<VertexData> {
    public:
        Geom(GLenum primitive_type);
        ~Geom();

        uint32_t getVerticesCount();

        template <typename Vertex>
        void addVertices(const fast_vector<Vertex>& vs);
        template <typename Vertex>
        void addVertex(const Vertex& v);
        template <typename Vertex>
        const Vertex& getVertex(uint32_t id)const;
        template <typename Vertex>
        Vertex& accVertex(uint32_t id);     // also sets dirty flag (will be updated to gpu on next sync)
        void removeVertex(uint32_t id);
        void removeAllVertices();

        template <typename Vertex>
        void collectVertices(fast_vector<Vertex>& vertices_out);

        void render();

        GLuint getIboGlHandle();
        GLenum getPrimitiveType();

        void syncWithGPU();

        template <typename T>
        T getFactory();
    protected:
        void removeVertexInner_(uint32_t id);

        GLuint ibo_;
        GLenum primitive_type_;
        fast_vector<uint32_t> indices_;      // ram copy of indices
        bool dirty_indices_;
    };
}

#include "Geom.inl"
#endif //GEOM_H
