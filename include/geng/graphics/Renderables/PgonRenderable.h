#ifndef POLYGONRENDERABLE_H
#define POLYGONRENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class SimpleColorShader;
    class VertexDataP;

    // Convex polygon
    class PgonRenderable : public Renderable {
    public:
        typedef SimpleColorShader ShaderType;
        typedef VertexDataP VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public Renderable::DrawData {
            DrawData() : color(1, 1, 1, 1) {}

            Colorf color;
        };

        void setNewGeom(GeomUsageHint usage_hint = DefaultUsageHint);

        // reuses internal static shared geom
        void setStaticSharedQuadGeom(NormOffset::Type offset_type = NormOffset::otCenter);

        Colorf getColor()const;
        Colorf& accColor();

        void setColor(const Colorf& clr);

        void onBeforeDraw(Shader& s);
    };

}

#include "PgonRenderable.inl"
#endif //POLYGONRENDERABLE_H
