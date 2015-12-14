#include "Geom.h"
#include "VertexData.h"

namespace grynca {

    inline Geom::Geom(GLenum primitive_type)
     : primitive_type_(primitive_type),
       dirty_indices_(true)
    {
        GLCall(glGenBuffers(1, &ibo_));
    }

    inline Geom::~Geom() {
        removeAllVertices();
        GLCall(glDeleteBuffers(1, &ibo_));
    }

    inline uint32_t Geom::getVerticesCount() {
        return uint32_t(indices_.size());
    }

    template <typename Vertex>
    inline void Geom::addVertices(const fast_vector<Vertex>& vs) {
        for (uint32_t i=0; i<vs.size(); ++i) {
            addVertex(vs[i]);
        }
    }

    template <typename Vertex>
    inline void Geom::addVertex(const Vertex& v) {
        VertexData& manager = getManager();
        uint32_t vert_id = manager.getVerticesCount();
        indices_.push_back(vert_id);
        dirty_indices_ = true;
        manager.vertices_data_.insert(manager.vertices_data_.end(), (uint8_t*)&v, (uint8_t*)(&v+1));
        manager.vertices_owner_.push_back(id_);
        manager.dirty_vertices_.push_back(vert_id);
    }

    template <typename Vertex>
    inline const Vertex& Geom::getVertex(uint32_t id)const {
        return getManager().getVertex_<Vertex>(indices_[id]);
    }

    template <typename Vertex>
    inline Vertex& Geom::accVertex(uint32_t id) {
        uint32_t vert_id = indices_[id];
        getManager().dirty_vertices_.push_back(vert_id);
        return getManager().getVertex_<Vertex>(vert_id);
    }

    inline void Geom::removeVertex(uint32_t id) {
        removeVertexInner_(id);
        indices_.erase(indices_.begin()+id);
        dirty_indices_ = true;
    }

    inline void Geom::removeAllVertices() {
        for (int i=(int)indices_.size()-1; i>=0; --i) {
            removeVertexInner_(i);
        }
        indices_.clear();
        dirty_indices_ = true;
    }

    inline void Geom::render() {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIboGlHandle()));
        GLCall(glDrawElements(getPrimitiveType(), getVerticesCount(), GL_UNSIGNED_INT, NULL));
    }

    inline GLuint Geom::getIboGlHandle() {
        return ibo_;
    }

    inline GLenum Geom::getPrimitiveType() {
        return primitive_type_;
    }

    inline void Geom::syncWithGPU() {
        if (!dirty_indices_)
            return;

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_));
        void *ptr = indices_.empty()? NULL:&indices_[0];
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indices_.size(), ptr, GL_DYNAMIC_DRAW));
        dirty_indices_ = false;
    }

    template <typename T>
    inline T Geom::getFactory() {
        return T(getManager(), getId());
    }

    inline void Geom::removeVertexInner_(uint32_t id) {
        uint32_t vert_id = indices_[id];
        VertexData& vd = getManager();
        uint32_t last_vert_id = vd.getVerticesCount()-1;
        if (last_vert_id != vert_id) {
            // replace removed vertex with last vertex
            memcpy(vd.getVertexRaw_(vert_id), vd.getVertexRaw_(last_vert_id), vd.getVertexSize());
            uint32_t last_vert_owner = vd.vertices_owner_[last_vert_id];
            vd.vertices_owner_[vert_id] = last_vert_owner;
            vd.dirty_vertices_.push_back(vert_id);
            // correct Geom's index for moved vertex
            Geom& geom = vd.getItem(last_vert_owner);
            size_t i;
            for (i=0; i<geom.indices_.size(); ++i) {
                if (geom.indices_[i] == last_vert_id) {
                    geom.indices_[i] = vert_id;
                    break;
                }
            }
            ASSERT(i!=geom.indices_.size(),
                   "Removed vertex index not found in its owner geom.");
            geom.dirty_indices_ = true;
        }

        vd.vertices_data_.resize(vd.vertices_data_.size()-vd.getVertexSize());
        vd.vertices_owner_.pop_back();
    }

}