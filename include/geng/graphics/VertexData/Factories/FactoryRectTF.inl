#include "FactoryRectTF.h"

#define FR_TPL template <typename VertexType>
#define FR_TYPE FactoryRectTF<VertexType>

namespace grynca {
    FR_TPL
    inline u32 FR_TYPE::add() {
        Geom& g = getGeom();
        u32 start = g.getVerticesCount();
        g.addVertex(VertexType{});      // left-top
        g.addVertex(VertexType{});      // right-top
        g.addVertex(VertexType{});      // right-bot
        g.addVertex(VertexType{});      // left-bot
        return start;
    }

    FR_TPL
    inline u32 FR_TYPE::add(const Vec2& size, const Vec2& offset) {
        u32 start = add();
        setSize(start, size);
        setOffset(start, offset);
        return start;
    }

    FR_TPL
    inline u32 FR_TYPE::add(const Vec2& size) {
        u32 start = add();
        setSize(start, size);
        setOffset(start, size/2);
        return start;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getLeftTop(u32 start)const {
        return getGeom().template getVertex<VertexType>(start).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getRightBot(u32 start)const {
        return getGeom().template getVertex<VertexType>(start+2).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getSize(u32 start)const {
        return getGeom().template getVertex<VertexType>(start+2).pos - getGeom().template getVertex<VertexType>(start).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getOffset(u32 start)const {
        return getGeom().template getVertex<VertexType>(start).pos;
    }

    FR_TPL
    inline void FR_TYPE::setSize(u32 start, const Vec2& size) {
        Geom& g = getGeom();
        Vec2 size_diff = size - getSize(start);
        g.template accVertex<VertexType>(start+1).pos.accX() += size_diff.getX();
        g.template accVertex<VertexType>(start+2).pos += size_diff;
        g.template accVertex<VertexType>(start+3).pos.accY() += size_diff.getY();
    }

    FR_TPL
    inline void FR_TYPE::setOffset(u32 start, const Vec2& offset) {
        Geom& g = getGeom();
        Vec2 offset_diff = offset - getOffset(start);

        VertexType& lt = g.template accVertex<VertexType>(start);
        VertexType& rt = g.template accVertex<VertexType>(start+1);
        VertexType& rb = g.template accVertex<VertexType>(start+2);
        VertexType& lb = g.template accVertex<VertexType>(start+3);
        lt.pos += offset_diff;
        rt.pos += offset_diff;
        rb.pos += offset_diff;
        lb.pos += offset_diff;
    }

    FR_TPL
    inline void FR_TYPE::setTC(u32 start, const Vec2& left_top, const Vec2& right_bot) {
        Geom& g = getGeom();
        g.template accVertex<VertexType>(start).tc = left_top;
        g.template accVertex<VertexType>(start+1).tc = Vec2(right_bot.getX(), left_top.getY());
        g.template accVertex<VertexType>(start+2).tc = right_bot;
        g.template accVertex<VertexType>(start+3).tc = Vec2(left_top.getX(), right_bot.getY());
    }

    FR_TPL
    inline Geom& FR_TYPE::getGeom()const {
        return geom_ref_.get();
    }

    FR_TPL
    inline FR_TYPE::FactoryRectTF(Geom& g)
     : geom_ref_(g)
            {}

    FR_TPL
    inline FR_TYPE::FactoryRectTF(VertexData& vertex_data, GeomState::StateType state_type, GeomState::UsageHint buff_hint)
     : geom_ref_(vertex_data.addItem(GL_TRIANGLE_FAN, state_type, buff_hint))
    {}

}

#undef FR_TPL
#undef FR_TYPE