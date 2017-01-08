#include "PgonRenderable.h"
#include "../Shaders/SimpleColorShader.h"
#include "../VertexData/VertexDataP.h"

namespace grynca {

    inline VertexData::ItemRef PgonRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataP& verts = w.getVertices().get<VertexDataP>();
        return verts.addItem(GL_TRIANGLE_FAN, GeomState::stNone, usage_hint);
    }

    inline Colorf PgonRenderable::getColor()const {
        return getRenderTask()->getUniformsAs<SimpleColorShader::Uniforms>().color;
    }

    inline Colorf& PgonRenderable::accColor() {
        return accRenderTask()->getUniformsAs<SimpleColorShader::Uniforms>().color;
    }

    inline PgonRenderable& PgonRenderable::setColor(const Colorf& clr) {
        accRenderTask()->getUniformsAs<SimpleColorShader::Uniforms>().color = clr;
        return *this;
    }

    inline PgonRenderable& PgonRenderable::setPosition(const Vec2& pos) {
        accRenderTask()->accLocalTransform().setPosition(pos);
        return *this;
    }
}