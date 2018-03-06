#include "Geom.h"
#include "VertexData.h"

namespace grynca {

    inline Geom::Geom(GLenum primitive_type, GeomUsageHint buff_hint)
     : buffer_id_(u16(InvalidId())), bits_pack_(0), primitive_type_(primitive_type), start_offset_in_vbo_(InvalidId()), verts_cnt_vbo_(0),
       state_id_(InvalidId()), left_(Index::Invalid()), right_(Index::Invalid())
    {
    setUsageHint_(buff_hint);
    }

    inline void Geom::afterAdded() {
        buffer_id_ = getManager().getBufferForNewGeom_(getUsageHint());
        // initial set dirty
        makeDirty_();
        //std::cout << "added geom " << getId() << std::endl;
    }

    inline Geom::~Geom() {
        if (buffer_id_ != u16(InvalidId())) {
            unlink_();
        }
    }

    inline u32 Geom::getVerticesCount()const {
        return u32(vertices_data_.size()/getManager().getVertexSize());
    }

    inline u32 Geom::getVerticesBytesSize()const {
        return u32(vertices_data_.size());
    }

    inline GeomUsageHint Geom::getUsageHint()const {
        return GeomUsageHint(GET_BITS(bits_pack_, BIT_USAGE_HINT_START, BIT_USAGE_HINT_CNT));
    }

    inline bool Geom::isDirty()const {
        return bool(GET_BIT(bits_pack_, BIT_DIRTY));
    }

    inline u16 Geom::getVertexBufferId()const {
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

        u32 pos = u32(vertices_data_.size());
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

    inline u32 Geom::getVertsCountVbo()const {
        return verts_cnt_vbo_;
    }

    inline void Geom::render() {
        ASSERT_M(start_offset_in_vbo_ != InvalidId(), "trying to render geom not placed in vbo.");
        GLCall(glDrawArrays(getPrimitiveType(), GLint(start_offset_in_vbo_), GLsizei(verts_cnt_vbo_)));
    }

    inline GLenum Geom::getPrimitiveType() {
        return primitive_type_;
    }

    template <typename T>
    inline T Geom::getFactory() {
        return T(*this);
    }

    inline GeomStateType Geom::getStateType()const {
        return GeomStateType(GET_BITS(bits_pack_, BIT_STATE_TYPE_START, BIT_STATE_TYPE_CNT));
    }

    inline u32 Geom::getStateId()const {
        return state_id_;
    }

    inline const GeomStateBase& Geom::getState()const {
        ASSERT(getStateType() != gstNone);
        return *getManager().getGeomStates().getState(getStateType(), getStateId());
    }

    inline GeomStateBase& Geom::accState() {
        ASSERT(getStateType() != gstNone);
        return *getManager().accGeomStates().accState(getStateType(), getStateId());
    }

    inline GeomStateBase* Geom::setState(GeomStateType st) {
        GeomStateType curr_state = getStateType();
        GeomStates& gss = getManager().accGeomStates();
        if (curr_state != gstNone) {
            gss.removeState(curr_state, getStateId());
        }
        bits_pack_ = SET_BITS(bits_pack_, BIT_STATE_TYPE_START, BIT_STATE_TYPE_CNT, u32(st));
        GeomStateBase* new_state = NULL;
        if (st != gstNone) {
            state_id_ = gss.getStatesCount(st);
            new_state = gss.addState(st, getId());
        }
        return new_state;
    }

    inline fast_vector<f32> Geom::loadDataFromGPU() {
        size_t size = verts_cnt_vbo_ * getManager().getVertexSize();
        fast_vector<f32> buf(size/sizeof(f32));
        glGetBufferSubData(GL_ARRAY_BUFFER, start_offset_in_vbo_, size, &buf[0]);
        return buf;
    }

    inline void Geom::setUsageHint_(GeomUsageHint buff_hint) {
        bits_pack_ = SET_BITS(bits_pack_, BIT_USAGE_HINT_START, BIT_USAGE_HINT_CNT, u32(buff_hint));
    }

    inline void Geom::setStateId_(u32 state_id) {
        state_id_ = state_id;
    }

    inline void Geom::link_(Index left, Index right) {
        left_ = left;
        if (left_.isValid()) {
            getManager().accItem(left_).right_ = getId();
        }

        right_ = right;
        if (right_.isValid()) {
            getManager().accItem(right_).left_= getId();
        }
    }

    inline void Geom::unlink_() {
        ASSERT(buffer_id_ != InvalidId());

        //std::cout << " removing geom " << getId() << std::endl;

        VertexBuffer& buf = getManager().buffers_[buffer_id_];

        if (buf.last_geom == getId()) {
            buf.last_geom = left_;
            buf.size -= verts_cnt_vbo_;
            u32 left_space = getSpaceOnLeft_();
            buf.size -= left_space;
            buf.holes_size -= left_space;
        }
        else {
            buf.holes_size += verts_cnt_vbo_;
        }

        if (left_.isValid()) {
            Geom& lg = getManager().accItem(left_);
            lg.right_ = right_;
        }
        if (right_.isValid()) {
            Geom& rg = getManager().accItem(right_);
            rg.left_ = left_;
        }
        left_ = Index::Invalid();
        right_ = Index::Invalid();
    }

    inline u32 Geom::getSpaceOnRight_() {
        u32 my_end = start_offset_in_vbo_ + verts_cnt_vbo_;
        if (!right_.isValid()) {
            return getManager().buffers_[buffer_id_].size - my_end;
        }
        // else
        Geom& rg = getManager().accItem(right_);
        return rg.start_offset_in_vbo_ - my_end;
    }

    inline u32 Geom::getSpaceOnLeft_() {
        if (!left_.isValid())
            return start_offset_in_vbo_;
        // else
        Geom& lg = getManager().accItem(left_);
        u32 left_end = lg.start_offset_in_vbo_ + lg.verts_cnt_vbo_;
        return start_offset_in_vbo_ - left_end;
    }

    inline void Geom::makeDirty_() {
        bits_pack_ = SET_BIT(bits_pack_, BIT_DIRTY);
        getManager().invalidateGeom_(*this);
    }

    inline void Geom::clearDirty_() {
        bits_pack_ = CLEAR_BIT(bits_pack_, BIT_DIRTY);
    }

}