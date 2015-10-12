#ifndef GEOM_UTILS_H
#define GEOM_UTILS_H

#include "maths/Vec2.h"
#include "Geom.h"

namespace grynca {

    namespace geom_utils {

        // GL_TRIANGLE_FAN rectangles
        namespace RectTF {
            template <typename VertexType>
            static uint32_t add(Geom& g) {
                uint32_t start = g.getVerticesCount();
                g.addVertex(VertexType{});      // left-top
                g.addVertex(VertexType{});      // right-top
                g.addVertex(VertexType{});      // right-bot
                g.addVertex(VertexType{});      // left-bot
                return start;
            }

            template <typename VertexType>
            static Vec2 getLeftTop(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start).pos;
            }

            template <typename VertexType>
            static Vec2 getRightBot(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+2).pos;
            }

            template <typename VertexType>
            static Vec2 getSize(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+2).pos - g.getVertex<VertexType>(start).pos;
            }

            template <typename VertexType>
            static Vec2 getOffset(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start).pos;
            }

            template <typename VertexType>
            static void setSize(Geom& g, uint32_t start, const Vec2& size) {
                Vec2 size_diff = size - getSize<VertexType>(g, start);
                g.accVertex<VertexType>(start+1).pos.accX() += size_diff.getX();
                g.accVertex<VertexType>(start+2).pos += size_diff;
                g.accVertex<VertexType>(start+3).pos.accY() += size_diff.getY();
            }

            template <typename VertexType>
            static void setOffset(Geom& g, uint32_t start, const Vec2& offset) {
                Vec2 offset_diff = offset - getOffset<VertexType>(g, start);
                g.accVertex<VertexType>(start).pos += offset_diff;
                g.accVertex<VertexType>(start+1).pos += offset_diff;
                g.accVertex<VertexType>(start+2).pos += offset_diff;
                g.accVertex<VertexType>(start+3).pos += offset_diff;
            }

            template <typename VertexType>
            static void setTC(Geom& g, uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
                g.accVertex<VertexType>(start).tc = left_top;
                g.accVertex<VertexType>(start+1).tc = Vec2(right_bot.getX(), left_top.getY());
                g.accVertex<VertexType>(start+2).tc = right_bot;
                g.accVertex<VertexType>(start+3).tc = Vec2(left_top.getX(), right_bot.getY());
            }
        }

        // GL_TRIANGLES rectangles
        namespace RectT {
            template <typename VertexType>
            static uint32_t add(Geom& g) {
                uint32_t start = g.getVerticesCount();
                g.addVertex(VertexType{});      // left-bot
                g.addVertex(VertexType{});      // left-top
                g.addVertex(VertexType{});      // right-bot
                g.addVertex(VertexType{});      // right-bot
                g.addVertex(VertexType{});      // left-top
                g.addVertex(VertexType{});      // right-top
                return start;
            }

            template <typename VertexType>
            static Vec2 getLeftTop(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+1).pos;
            }

            template <typename VertexType>
            static Vec2 getRightBot(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+2).pos;
            }

            template <typename VertexType>
            static Vec2 getSize(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+2).pos - g.getVertex<VertexType>(start+1).pos;
            }

            template <typename VertexType>
            static Vec2 getOffset(Geom& g, uint32_t start) {
                return g.getVertex<VertexType>(start+1).pos;
            }

            template <typename VertexType>
            static void setSize(Geom& g, uint32_t start, const Vec2& size) {
                Vec2 size_diff = size - getSize<VertexType>(g, start);
                g.accVertex<VertexType>(start).pos.accY() += size_diff.getY();
                g.accVertex<VertexType>(start+2).pos += size_diff;
                g.accVertex<VertexType>(start+3).pos += size_diff;
                g.accVertex<VertexType>(start+5).pos.accX() += size_diff.getX();
            }

            template <typename VertexType>
            static void setOffset(Geom& g, uint32_t start, const Vec2& offset) {
                Vec2 offset_diff = offset - getOffset<VertexType>(g, start);
                g.accVertex<VertexType>(start).pos += offset_diff;
                g.accVertex<VertexType>(start+1).pos += offset_diff;
                g.accVertex<VertexType>(start+2).pos += offset_diff;
                g.accVertex<VertexType>(start+3).pos += offset_diff;
                g.accVertex<VertexType>(start+4).pos += offset_diff;
                g.accVertex<VertexType>(start+5).pos += offset_diff;
            }

            template <typename VertexType>
            static void setTC(Geom& g, uint32_t start, const Vec2& left_top, const Vec2& right_bot) {
                g.accVertex<VertexType>(start).tc = Vec2(left_top.getX(), right_bot.getY());
                g.accVertex<VertexType>(start+1).tc = left_top;
                g.accVertex<VertexType>(start+2).tc = right_bot;
                g.accVertex<VertexType>(start+3).tc = right_bot;
                g.accVertex<VertexType>(start+4).tc = left_top;
                g.accVertex<VertexType>(start+5).tc = Vec2(right_bot.getX(), left_top.getY());
            }
        }
    }

}

#endif //GEOM_UTILS_H
