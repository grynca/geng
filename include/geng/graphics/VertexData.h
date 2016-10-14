#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "glinclude.h"
#include "types/Manager.h"
#include <stdint.h>
#include <unordered_set>

namespace grynca {

    // fw
    class Geom;
    class Vertices;

    struct VertexAttribInfo {
        uint32_t count;
        GLenum type;
        bool normalized;
        uint32_t struct_offset;
    };

    class VertexData : public ManagedItemSingleton<Vertices>,
                       public Manager<Geom> {
        friend class Geom;
    public:
        VertexData();
        virtual ~VertexData();

        void bind();

        template <typename Vertex>
        void setVertexAttribs(const fast_vector<VertexAttribInfo>& attribs);

        uint32_t getVerticesCount();
        uint32_t getVertexSize();
        GLuint getVaoHandle();
        GLuint getVboHandle();

        void syncWithGPU();

        template <typename T>
        T addWithFactory();

        template <typename Vertex>
        void collectVertices(fast_vector<Vertex>& vertices_out);        // for debug mostly
    protected:
        template <typename Vertex>
        Vertex& getVertex_(uint32_t id);
        uint8_t* getVertexRaw_(uint32_t id);

        fast_vector<uint8_t> vertices_data_;    // RAM copy of all vertices
        fast_vector<Index> vertices_owner_;  // for each vertex id of owning geom
        std::unordered_set<uint32_t> dirty_vertices_;  // indices of vertices in need of syncing to GPU

        uint32_t vertex_size_;
        GLuint vao_;
        GLuint vbo_;
    };

}

#include "VertexData.inl"
#endif //VERTEXDATA_H
