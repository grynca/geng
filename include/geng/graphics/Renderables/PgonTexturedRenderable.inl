#include "PgonTexturedRenderable.h"
#include "../Shaders/SimpleTexturedShader.h"
#include "../VertexData/VertexDataPT.h"

namespace grynca {

    inline VertexData::ItemRef PgonTexturedRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataPT& verts = w.getVertices().get<VertexDataPT>();
        return verts.addItem(GL_TRIANGLE_FAN, GeomState::stNone, usage_hint);
    }

    inline PgonTexturedRenderable& PgonTexturedRenderable::setTextureUnit(u32 tid) {
        accRenderTask()->getUniformsAs<SimpleTexturedShader::Uniforms>().texture = tid;
        return *this;
    }

    inline PgonTexturedRenderable& PgonTexturedRenderable::setPosition(const Vec2& pos) {
        accRenderTask()->accLocalTransform().setPosition(pos);
        return *this;
    }

    inline u32 PgonTexturedRenderable::getTextureUnit()const {
        return getRenderTask()->getUniformsAs<SimpleTexturedShader::Uniforms>().texture;
    }
}