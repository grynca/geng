#ifndef FACTORYRECTT_H
#define FACTORYRECTT_H

#include "maths/Vec2.h"
#include "../Geom.h"

namespace grynca {

    // GL_TRIANGLES rectangles
    template <typename VertexType>
    class FactoryRectT {
    public:
        // returns start vertex id of newly added rect
        u32 add();
        u32 add(const Vec2& size, const Vec2& offset);
        u32 add(const Vec2& size);

        Vec2 getLeftTop(u32 start)const;
        Vec2 getRightBot(u32 start)const;
        Vec2 getSize(u32 start)const;
        Vec2 getOffset(u32 start)const;

        void setSize(u32 start, const Vec2& size);
        void setOffset(u32 start, const Vec2& offset);
        void setTC(u32 start, const Vec2& left_top, const Vec2& right_bot);

        Geom& getGeom()const;

    private:
        friend class Geom;
        friend class VertexData;

        FactoryRectT(Geom& g);
        FactoryRectT(VertexData& vertex_data, GeomUsageHint buff_hint);

        Geom& geom_;
    };
}

#include "FactoryRectT.inl"
#endif //FACTORYRECTT_H
