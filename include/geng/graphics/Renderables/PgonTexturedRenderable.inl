#include "PgonTexturedRenderable.h"
#include "../Shaders/SimpleTexturedShader.h"
#include "../VertexData/VertexDataPT.h"

namespace grynca {

    inline void PgonTexturedRenderable::setNewGeom(GeomUsageHint usage_hint) {
        VertexDataPT& verts = accWindow().getVertices().getFast<VertexDataPT>();
        setGeom(verts.addItem(GL_TRIANGLE_FAN, usage_hint));
    }

    inline void PgonTexturedRenderable::setTextureUnit(u32 tid) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().texture = tid;
    }

    inline u32 PgonTexturedRenderable::getTextureUnit()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().texture;
    }

    inline void PgonTexturedRenderable::onBeforeDraw(Shader& s) {
        SimpleTexturedShader& sts = (SimpleTexturedShader&)s;
        sts.setUniforms(accRenderTaskPtr()->getDrawDataAs<DrawData>());
    }
}