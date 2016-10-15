#ifndef FACTORYRECTT_H
#define FACTORYRECTT_H

#include "maths/Vec2.h"
#include "geng/graphics/Geom.h"

namespace grynca {

    // GL_TRIANGLES rectangles
    template <typename VertexType>
    class FactoryRectT {
    public:

        // returns start vertex id of newly added rect
        uint32_t add();
        uint32_t add(const Vec2& size, const Vec2& offset);
        uint32_t add(const Vec2& size);

        Vec2 getLeftTop(uint32_t start)const;
        Vec2 getRightBot(uint32_t start)const;
        Vec2 getSize(uint32_t start)const;
        Vec2 getOffset(uint32_t start)const;

        void setSize(uint32_t start, const Vec2& size);
        void setOffset(uint32_t start, const Vec2& offset);
        void setTC(uint32_t start, const Vec2& left_top, const Vec2& right_bot);

        Geom& getGeom()const;

    private:
        friend class Geom;
        friend class VertexData;

        FactoryRectT(Geom& g);
        FactoryRectT(VertexData& vertex_data);

        VertexData::ItemRef geom_ref_;
    };
}

#include "FactoryRectT.inl"
#endif //FACTORYRECTT_H
