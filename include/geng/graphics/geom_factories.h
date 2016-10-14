#ifndef GEOM_FACTORIES_H
#define GEOM_FACTORIES_H

#include "maths/Vec2.h"
#include "Geom.h"

namespace grynca {

    // GL_TRIANGLE_FAN rectangles
    template <typename VertexType>
    class FactoryRectTF {
    public:
        // returns start vertex id of newly added rect
        uint32_t add() {
            Geom& g = getGeom();
            uint32_t start = g.getVerticesCount();
            g.addVertex(VertexType{});      // left-top
            g.addVertex(VertexType{});      // right-top
            g.addVertex(VertexType{});      // right-bot
            g.addVertex(VertexType{});      // left-bot
            return start;
        }

        uint32_t add(const Vec2& size, const Vec2& offset) {
            uint32_t start = add();
            setSize(start, size);
            setOffset(start, offset);
            return start;
        }

        uint32_t add(const Vec2& size) {
            uint32_t start = add();
            setSize(start, size);
            setOffset(start, size/2);
            return start;
        }

        Vec2 getLeftTop(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start).pos;
        }

        Vec2 getRightBot(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+2).pos;
        }

        Vec2 getSize(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+2).pos - getGeom().template getVertex<VertexType>(start).pos;
        }

        Vec2 getOffset(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start).pos;
        }

        void setSize(uint32_t start, const Vec2& size) {
            Geom& g = getGeom();
            Vec2 size_diff = size - getSize(start);
            g.template accVertex<VertexType>(start+1).pos.accX() += size_diff.getX();
            g.template accVertex<VertexType>(start+2).pos += size_diff;
            g.template accVertex<VertexType>(start+3).pos.accY() += size_diff.getY();
        }

        void setOffset(uint32_t start, const Vec2& offset) {
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

        void setTC(uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
            Geom& g = getGeom();
            g.template accVertex<VertexType>(start).tc = left_top;
            g.template accVertex<VertexType>(start+1).tc = Vec2(right_bot.getX(), left_top.getY());
            g.template accVertex<VertexType>(start+2).tc = right_bot;
            g.template accVertex<VertexType>(start+3).tc = Vec2(left_top.getX(), right_bot.getY());
        }

        Geom& getGeom()const {
            return vertex_data_->getItem(geom_id_);
        }

    private:
        friend class Geom;
        friend class VertexData;

        FactoryRectTF(VertexData& vertex_data, Index geom_id)
         : vertex_data_(&vertex_data), geom_id_(geom_id)
        {}

        FactoryRectTF(VertexData& vertex_data)
         : vertex_data_(&vertex_data), geom_id_(vertex_data.addItem(GL_TRIANGLE_FAN).getId())
        {}

        VertexData* vertex_data_;
        Index geom_id_;
    };

    // GL_TRIANGLES rectangles
    template <typename VertexType>
    class FactoryRectT {
    public:
        uint32_t add() {
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

        uint32_t add(const Vec2& size, const Vec2& offset) {
            uint32_t start = add();
            setSize(start, size);
            setOffset(start, offset);
            return start;
        }

        uint32_t add(const Vec2& size) {
            uint32_t start = add();
            setSize(start, size);
            setOffset(start, size/2);
            return start;
        }

        Vec2 getLeftTop(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+1).pos;
        }

        Vec2 getRightBot(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+2).pos;
        }

        Vec2 getSize(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+2).pos - getGeom().template getVertex<VertexType>(start+1).pos;
        }

        Vec2 getOffset(uint32_t start)const {
            return getGeom().template getVertex<VertexType>(start+1).pos;
        }

        void setSize(uint32_t start, const Vec2& size) {
            Geom& g = getGeom();
            Vec2 size_diff = size - getSize(start);
            g.template accVertex<VertexType>(start).pos.accY() += size_diff.getY();
            g.template accVertex<VertexType>(start+2).pos += size_diff;
            g.template accVertex<VertexType>(start+3).pos += size_diff;
            g.template accVertex<VertexType>(start+5).pos.accX() += size_diff.getX();
        }

        void setOffset(uint32_t start, const Vec2& offset) {
            Geom& g = getGeom();
            Vec2 offset_diff = offset - getOffset(start);
            g.template accVertex<VertexType>(start).pos += offset_diff;
            g.template accVertex<VertexType>(start+1).pos += offset_diff;
            g.template accVertex<VertexType>(start+2).pos += offset_diff;
            g.template accVertex<VertexType>(start+3).pos += offset_diff;
            g.template accVertex<VertexType>(start+4).pos += offset_diff;
            g.template accVertex<VertexType>(start+5).pos += offset_diff;
        }

        void setTC(uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
            Geom& g = getGeom();
            g.template accVertex<VertexType>(start).tc = Vec2(left_top.getX(), right_bot.getY());
            g.template accVertex<VertexType>(start+1).tc = left_top;
            g.template accVertex<VertexType>(start+2).tc = right_bot;
            g.template accVertex<VertexType>(start+3).tc = right_bot;
            g.template accVertex<VertexType>(start+4).tc = left_top;
            g.template accVertex<VertexType>(start+5).tc = Vec2(right_bot.getX(), left_top.getY());
        }

        Geom& getGeom()const {
            return vertex_data_->getItem(geom_id_);
        }

    private:
        friend class Geom;
        friend class VertexData;

        FactoryRectT(VertexData& vertex_data, Index geom_id)
         : vertex_data_(&vertex_data), geom_id_(geom_id)
        {}

        FactoryRectT(VertexData& vertex_data)
         : vertex_data_(&vertex_data), geom_id_(vertex_data_->addItem(GL_TRIANGLES).getId())
        {}

        VertexData* vertex_data_;
        Index geom_id_;
    };
}

#endif //GEOM_FACTORIES_H
