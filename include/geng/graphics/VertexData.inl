#include "VertexData.h"
#include "Vertices.h"
#include "Geom.h"
#include <cassert>

namespace grynca {

    inline VertexData::VertexData()
     : vertex_size_(0)
    {
        GLCall(glGenVertexArrays(1, &vao_));
        GLCall(glGenBuffers(1, &vbo_));
    }

    inline VertexData::~VertexData() {
        GLCall(glDeleteVertexArrays(1, &vao_));
        GLCall(glDeleteBuffers(1, &vbo_));
    }

    inline void VertexData::bind() {
        if (getManager().bound_id_ == getId())
            return;

        GLCall(glBindVertexArray(getVaoHandle()));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, getVboHandle()));
        getManager().bound_id_ = getId();
    }

    template <typename Vertex>
    inline void VertexData::setVertexAttribs(const fast_vector<VertexAttribInfo>& attribs) {
        GLCall(glBindVertexArray(vao_));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_));

        vertex_size_ = uint32_t(sizeof(Vertex));
        for (uint32_t i=0; i<attribs.size(); ++i) {
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, attribs[i].count, attribs[i].type, (GLboolean)attribs[i].normalized, vertex_size_, reinterpret_cast<const GLvoid*>(attribs[i].struct_offset)));
        }
    }

    inline uint32_t VertexData::getVerticesCount() {
        ASSERT(vertex_size_!=0, "Invalid vertex size.");
        return uint32_t(vertices_data_.size())/vertex_size_;
    }

    inline uint32_t VertexData::getVertexSize() {
        return vertex_size_;
    }

    inline GLuint VertexData::getVaoHandle() {
        return vao_;
    }

    inline GLuint VertexData::getVboHandle() {
        return vbo_;
    }

    inline void VertexData::syncWithGPU() {
        if (dirty_vertices_.empty())
            return;

        bind();

        uint32_t needed_space = (uint32_t)vertices_data_.size();
//        if (needed_space > vbo_allocation_) {
//            // realloc buffer on gpu
//            GLuint buf;
//            glGenBuffers(1, &buf);
//            uint32_t prev_alloc = vbo_allocation_;
//            vbo_allocation_ = needed_space;
//            glBindBuffer(GL_ARRAY_BUFFER, buf);
//            glBufferData(GL_ARRAY_BUFFER, vbo_allocation_, NULL, GL_STATIC_DRAW);
//            if (prev_alloc != 0) {
//                glBindBuffer(GL_COPY_READ_BUFFER, vbo_);
//                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, prev_alloc);
//                glBindBuffer(GL_COPY_READ_BUFFER, 0);
//            }
//            glDeleteBuffers(1, &vbo_);
//            vbo_ = buf;
//        }
//        else
//            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
//        // update dirty vertices
//        PTGeom::Vertex* verts_gpu = (PTGeom::Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//        for (size_t i=0; i<dirty_vertices_.size(); ++i) {
//            uint32_t vert_id = dirty_vertices_[i];
//            verts_gpu[vert_id] = vertices_[vert_id];
//        }
//        glUnmapBuffer(GL_ARRAY_BUFFER);
        void *data = needed_space?&vertices_data_[0]:NULL;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_));
        GLCall(glBufferData(GL_ARRAY_BUFFER, needed_space, data, GL_STATIC_DRAW));
        dirty_vertices_.clear();


        for (uint32_t i=0; i<getItemsCount(); ++i) {
            getItemAtPos(i).syncWithGPU();
        }
    }

    template <typename T>
    inline T VertexData::addWithFactory() {
        return T(*this);
    }

    template <typename Vertex>
    inline Vertex& VertexData::getVertex_(uint32_t id) {
        ASSERT(vertex_size_!=0, "Invalid vertex size.");
        ASSERT(vertex_size_==sizeof(Vertex), "Template vertex is of different size than expected.");
        return *(Vertex*)&vertices_data_[id*vertex_size_];
    }

    inline uint8_t* VertexData::getVertexRaw_(uint32_t id) {
        return &vertices_data_[id*vertex_size_];
    }
}