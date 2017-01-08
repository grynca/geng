#ifndef FACTORYRECTTF_H
#define FACTORYRECTTF_H

#include "maths/Vec2.h"
#include "../Geom.h"

namespace grynca {

    // GL_TRIANGLE_FAN rectangles
    template <typename VertexType>
    class FactoryRectTF {
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

        FactoryRectTF(Geom& g);
        FactoryRectTF(VertexData& vertex_data, GeomState::StateType state_type, GeomState::UsageHint buff_hint);


        VertexData::ItemRef geom_ref_;
    };
}

#include "FactoryRectTF.inl"
#endif //FACTORYRECTTF_H
