#include "Geom.h"
#include "VertexData.h"

namespace grynca {

    inline Geom::Geom(GLenum primitive_type, GeomState::StateType state_type, GeomState::UsageHint buff_hint)
     : pack_(0), primitive_type_(primitive_type), buffer_id_(InvalidId()), start_offset_in_vbo_(InvalidId()), verts_cnt_vbo_(0),
       left_(Index::Invalid()), right_(Index::Invalid()), state_(state_type, buff_hint)
    {
    }

    inline void Geom::init() {
        buffer_id_ = getManager().getBufferForNewGeom_(state_.getUsageHint());

        // initial set state
        Index new_state_id = getManager().beforeGeomChangedState_(*this, GeomState::stNone, state_.getType());
        state_.setIndex(new_state_id);

        // initial set dirty
        pack_ = SET_BIT(pack_, 0);
        getManager().invalidateGeom_(*this);
    }

    inline Geom::~Geom() {
        if (buffer_id_ != InvalidId()) {
            unlink_();
        }

        getManager().beforeGeomChangedState_(*this, state_.getType(), GeomState::stNone);
    }

    inline u32 Geom::getVerticesCount()const {
        return vertices_data_.size()/getManager().getVertexSize();
    }

    inline u32 Geom::getVerticesBytesSize()const {
        return vertices_data_.size();
    }

    inline bool Geom::isDirty()const {
        return GET_BIT(pack_, 0);
    }

    inline u32 Geom::getVertexBufferId()const {
        return buffer_id_;
    }

    template <typename Vertex>
    inline void Geom::addVertices(const fast_vector<Vertex>& vs) {
        for (u32 i=0; i<vs.size(); ++i) {
            addVertex(vs[i]);
        }
    }

    template <typename Vertex>
    inline void Geom::addVertex(const Vertex& v) {
        ASSERT(sizeof(Vertex)==getManager().getVertexSize());

        if (!isDirty()) {
            makeDirty_();
        }

        u32 pos = vertices_data_.size();
        vertices_data_.resize(vertices_data_.size() + sizeof(Vertex));
        memcpy(&vertices_data_[pos], &v, sizeof(Vertex));
    }

    template <typename Vertex>
    inline const Vertex& Geom::getVertex(u32 id)const {
        ASSERT(id < getVerticesCount());
        ASSERT(sizeof(Vertex)==getManager().getVertexSize());

        return *(Vertex*)&vertices_data_[id*sizeof(Vertex)];
    }

    template <typename Vertex>
    inline Vertex& Geom::accVertex(u32 id) {
        ASSERT(id < getVerticesCount());
        ASSERT(sizeof(Vertex)==getManager().getVertexSize());
        if (!isDirty()) {
            makeDirty_();
        }
        return *(Vertex*)&vertices_data_[id*sizeof(Vertex)];
    }

    inline void Geom::removeVertex(u32 id) {
        ASSERT(id < getVerticesCount());
        if (!isDirty()) {
            makeDirty_();
        }
        u32 vert_size = getManager().getVertexSize();
        u32 from = id*vert_size;
        u32 to = from + vert_size;
        vertices_data_.erase(vertices_data_.begin() + from, vertices_data_.begin() + to);
    }

    inline void Geom::removeAllVertices() {
        if (!isDirty()) {
            makeDirty_();
        }
        vertices_data_.resize(0);
    }

    template <typename Vertex>
    inline void Geom::collectVertices(fast_vector<Vertex>& vertices_out) {
        vertices_out.reserve(vertices_out.size() + getVerticesCount());
        for (u32 i=0; i<getVerticesCount(); ++i) {
            vertices_out.push_back(getVertex<Vertex>(i));
        }
    }

    inline void Geom::render() {
        ASSERT_M(start_offset_in_vbo_ != InvalidId(), "trying to render geom not placed in vbo.");
        if (verts_cnt_vbo_ > 0) {
            GLCall(glDrawArrays(getPrimitiveType(), GLint(start_offset_in_vbo_), GLsizei(verts_cnt_vbo_)));
        }
    }

    inline GLenum Geom::getPrimitiveType() {
        return primitive_type_;
    }

    template <typename T>
    inline T Geom::getFactory() {
        return T(*this);
    }

    inline GeomState::StateType Geom::getGeomStateType()const {
        return state_.getType();
    }

    inline void Geom::setGeomStateType(GeomState::StateType st) {
        if (st != state_.getType()) {
            Index new_state_id = getManager().beforeGeomChangedState_(*this, state_.getType(), st);
            state_.setIndex(new_state_id);
        }
    }

    inline Index Geom::getGeomStateId()const {
        return state_.getIndex();
    }

    inline fast_vector<float> Geom::loadDataFromGPU() {
        size_t size = verts_cnt_vbo_ * getManager().getVertexSize();
        fast_vector<float> buf(size/sizeof(float));
        glGetBufferSubData(GL_ARRAY_BUFFER, start_offset_in_vbo_, size, &buf[0]);
        return buf;
    }

    inline void Geom::link_(Index left, Index right) {
        left_ = left;
        if (left_.isValid()) {
            getManager().getItem(left_).right_ = getId();
        }

        right_ = right;
        if (right_.isValid()) {
            getManager().getItem(right_).left_= getId();
        }
    }

    inline void Geom::unlink_() {
        ASSERT(buffer_id_ != InvalidId());

        if (getManager().buffers_[buffer_id_].last_geom == getId()) {
            getManager().buffers_[buffer_id_].last_geom = left_;
        }
        if (left_.isValid()) {
            getManager().getItem(left_).right_ = right_;
            left_ = Index::Invalid();
        }
        if (right_.isValid()) {
            getManager().getItem(right_).left_ = left_;
            right_ = Index::Invalid();
        }
    }

    inline u32 Geom::getSpaceOnRight_() {
        ASSERT(right_.isValid());
        u32 my_end = start_offset_in_vbo_ + verts_cnt_vbo_;
        return getManager().getItem(right_).start_offset_in_vbo_ - my_end;
    }

    inline u32 Geom::getSpaceOnLeft_() {
        ASSERT(left_.isValid());
        Geom& lg = getManager().getItem(left_);
        u32 left_end = lg.start_offset_in_vbo_ + lg.verts_cnt_vbo_;
        return start_offset_in_vbo_ - left_end;
    }

    inline void Geom::makeDirty_() {
        pack_ = SET_BIT(pack_, 0);
        getManager().invalidateGeom_(*this);
    }

    inline void Geom::clearDirty_() {
        pack_ = CLEAR_BIT(pack_,0);
    }

}