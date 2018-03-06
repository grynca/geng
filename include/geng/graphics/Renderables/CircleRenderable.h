#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class CircleShader;
    class VertexDataP;

    class CircleRenderable : public Renderable {
    public:
        typedef CircleShader ShaderType;
        typedef VertexDataP VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public Renderable::DrawData {
            Colorf color;
            Vec2 r_range;
        };

        void setNewGeom(GeomUsageHint usage_hint = DefaultUsageHint);
        // reuses internal static geom
        void setStaticSharedGeom();

        f32 getInnerRadius()const;
        f32 getOuterRadius()const;
        Colorf getColor()const;

        void setColor(const Colorf& c) ;
        void setInnerRadius(f32 inner_r);
        void setOuterRadius(f32 outer_r);

        void onBeforeDraw(Shader& s);
    };
}

#include "CircleRenderable.inl"
#endif //CIRCLERENDERABLE_H
