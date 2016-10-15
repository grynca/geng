#include "FactoryRectT.h"

#define FR_TPL template <typename VertexType>
#define FR_TYPE FactoryRectT<VertexType>

namespace grynca {

    FR_TPL
    inline uint32_t FR_TYPE::add() {
        Geom& g = getGeom();
        uint32_t start = g.getVerticesCount();
        g.addVertex(VertexType{});      // left-bot
        g.addVertex(VertexType{});      // left-top
        g.addVertex(VertexType{});      // right-bot
        g.addVertex(VertexType{});      // right-bot
        g.addVertex(VertexType{});      // left-top
        g.addVertex(VertexType{});      // right-top
        return start;
    }

    FR_TPL
    inline uint32_t FR_TYPE::add(const Vec2& size, const Vec2& offset) {
        uint32_t start = add();
        setSize(start, size);
        setOffset(start, offset);
        return start;
    }

    FR_TPL
    inline uint32_t FR_TYPE::add(const Vec2& size) {
        uint32_t start = add();
        setSize(start, size);
        setOffset(start, size/2);
        return start;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getLeftTop(uint32_t start)const {
        return getGeom().template getVertex<VertexType>(start+1).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getRightBot(uint32_t start)const {
        return getGeom().template getVertex<VertexType>(start+2).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getSize(uint32_t start)const {
        return getGeom().template getVertex<VertexType>(start+2).pos - getGeom().template getVertex<VertexType>(start+1).pos;
    }

    FR_TPL
    inline Vec2 FR_TYPE::getOffset(uint32_t start)const {
        return getGeom().template getVertex<VertexType>(start+1).pos;
    }

    FR_TPL
    inline void FR_TYPE::setSize(uint32_t start, const Vec2& size) {
        Geom& g = getGeom();
        Vec2 size_diff = size - getSize(start);
        g.template accVertex<VertexType>(start).pos.accY() += size_diff.getY();
        g.template accVertex<VertexType>(start+2).pos += size_diff;
        g.template accVertex<VertexType>(start+3).pos += size_diff;
        g.template accVertex<VertexType>(start+5).pos.accX() += size_diff.getX();
    }

    FR_TPL
    inline void FR_TYPE::setOffset(uint32_t start, const Vec2& offset) {
        Geom& g = getGeom();
        Vec2 offset_diff = offset - getOffset(start);
        g.template accVertex<VertexType>(start).pos += offset_diff;
        g.template accVertex<VertexType>(start+1).pos += offset_diff;
        g.template accVertex<VertexType>(start+2).pos += offset_diff;
        g.template accVertex<VertexType>(start+3).pos += offset_diff;
        g.template accVertex<VertexType>(start+4).pos += offset_diff;
        g.template accVertex<VertexType>(start+5).pos += offset_diff;
    }

    FR_TPL
    inline void FR_TYPE::setTC(uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
        Geom& g = getGeom();
        g.template accVertex<VertexType>(start).tc = Vec2(left_top.getX(), right_bot.getY());
        g.template accVertex<VertexType>(start+1).tc = left_top;
        g.template accVertex<VertexType>(start+2).tc = right_bot;
        g.template accVertex<VertexType>(start+3).tc = right_bot;
        g.template accVertex<VertexType>(start+4).tc = left_top;
        g.template accVertex<VertexType>(start+5).tc = Vec2(right_bot.getX(), left_top.getY());
    }

    FR_TPL
    inline Geom& FR_TYPE::getGeom()const {
        return geom_ref_.get();
    }

    FR_TPL
    inline FR_TYPE::FactoryRectT(Geom& g)
     : geom_ref_(g)
    {}

    FR_TPL
    inline FR_TYPE::FactoryRectT(VertexData& vertex_data)
     : geom_ref_(vertex_data.addItem(GL_TRIANGLES))
    {}
}


#undef FR_TPL
#undef FR_TYPE