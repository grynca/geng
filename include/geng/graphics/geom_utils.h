#ifndef GEOM_UTILS_H
#define GEOM_UTILS_H

#include "maths/Vec2.h"
#include "Geom.h"

namespace grynca {

    namespace geom_utils {

        template <typename VertexType>
        static uint32_t addRect(Geom& g) {
            uint32_t start = g.getVerticesCount();
            g.addVertex(VertexType{});
            g.addVertex(VertexType{});
            g.addVertex(VertexType{});
            g.addVertex(VertexType{});
            return start;
        }

        template <typename VertexType>
        static Vec2 getRectSize(Geom& g, uint32_t start) {
            return g.getVertex<VertexType>(start+2).pos - g.getVertex<VertexType>(start).pos;
        }

        template <typename VertexType>
        static Vec2 getRectOffset(Geom& g, uint32_t start) {
            return g.getVertex<VertexType>(start).pos;
        }

        template <typename VertexType>
        static void setRectSize(Geom& g, uint32_t start, const Vec2& size) {
            Vec2 size_diff = size - getRectSize<VertexType>(g, start);
            g.accVertex<VertexType>(start+1).pos.accX() += size_diff.getX();
            g.accVertex<VertexType>(start+2).pos += size_diff;
            g.accVertex<VertexType>(start+3).pos.accY() += size_diff.getY();
        }

        template <typename VertexType>
        static void setRectOffset(Geom& g, uint32_t start, const Vec2& offset) {
            Vec2 offset_diff = offset - getRectOffset<VertexType>(g, start);
            g.accVertex<VertexType>(start).pos += offset_diff;
            g.accVertex<VertexType>(start+1).pos += offset_diff;
            g.accVertex<VertexType>(start+2).pos += offset_diff;
            g.accVertex<VertexType>(start+3).pos += offset_diff;
        }

        template <typename VertexType>
        static void setRectTC(Geom& g, uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
            g.accVertex<VertexType>(start).tc = left_top;
            g.accVertex<VertexType>(start+1).tc = Vec2(right_bot.getX(), left_top.getY());
            g.accVertex<VertexType>(start+2).tc = right_bot;
            g.accVertex<VertexType>(start+3).tc = Vec2(left_top.getX(), right_bot.getY());
        }
    }

}

#endif //GEOM_UTILS_H
