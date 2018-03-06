#ifndef RECTBORDERRENDERABLE_H
#define RECTBORDERRENDERABLE_H

#include "RectRenderable.h"

namespace grynca {

    //fw
    class RectBorderShader;

    class RectBorderRenderable : public RectRenderable {
    public:
        typedef RectBorderShader ShaderType;
        typedef typename RectRenderable::VertexDataType VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public RectRenderable::DrawData {
            Vec2 borders;
            Vec2 offset;
        };

        void setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint = DefaultUsageHint);
        // reuses internal static geom for common offset
        void setStaticSharedQuadGeom(NormOffset::Type offset_type);

        Vec2 getNormBorders()const;
        Vec2 getBordersPx()const;
        Vec2 getGeomNormOffset();

        void setColor(const Colorf& clr);
        void setGeomNormOffset(const Vec2& offset);
        void setNormBorders(Vec2 borders);     // [0-1] normalized to size
        void setSize(const Vec2& size, bool scale_borders = true);
        void setBordersPx(Vec2 borders_px);

        void onBeforeDraw(Shader& s);
    };
}

#include "RectBorderRenderable.inl"
#endif //RECTBORDERRENDERABLE_H
