#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "PgonRenderable.h"

namespace grynca {

    class RectRenderable : public PgonRenderable {
    public:
        typedef typename PgonRenderable::ShaderType ShaderType;
        typedef typename PgonRenderable::VertexDataType VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public PgonRenderable::DrawData {
            DrawData() : size(1, 1) {}

            Vec2 size;
        };

        static Geom& createNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint = DefaultUsageHint);

        void setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint = DefaultUsageHint);

        Vec2 getGeomNormOffset()const;
        Vec2 getSize()const;
        Vec2 getOffset()const;

        void setGeomNormOffset(const Vec2& offset);
        void setSize(const Vec2& size);

        Vec2& accSize();

        void onBeforeDraw(Shader& s);
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
