#ifndef PGONTEXTUREDRENDERABLE_H
#define PGONTEXTUREDRENDERABLE_H

#include "PgonRenderable.h"

namespace grynca {

    // fw
    class SimpleTexturedShader;
    class VertexDataPT;

    class PgonTexturedRenderable : public PgonRenderable {
    public:
        typedef SimpleTexturedShader ShaderType;
        typedef VertexDataPT VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public PgonRenderable::DrawData {
            u32 texture;
        };

        void setNewGeom(GeomUsageHint usage_hint = DefaultUsageHint);

        void setTextureUnit(u32 tid);
        u32 getTextureUnit()const;

        void onBeforeDraw(Shader& s);
    };

};

#include "PgonTexturedRenderable.inl"
#endif //PGONTEXTUREDRENDERABLE_H
