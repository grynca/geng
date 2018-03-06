#include "PgonRenderable.h"
#include "../Shaders/SimpleColorShader.h"
#include "../VertexData/VertexDataP.h"

namespace grynca {

    inline void PgonRenderable::setNewGeom(GeomUsageHint usage_hint) {
        VertexDataP& verts = accWindow().getVertices().getFast<VertexDataP>();
        setGeom(verts.addItem(GL_TRIANGLE_FAN, usage_hint));
    }

    inline void PgonRenderable::setStaticSharedQuadGeom(NormOffset::Type offset_type) {
        VertexDataP& verts = accWindow().getVertices().getFast<VertexDataP>();
        render_task_ptr_->setGeom(verts.accSharedUnitQuadGeom(offset_type));
    }

    inline Colorf PgonRenderable::getColor()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().color;
    }

    inline Colorf& PgonRenderable::accColor() {
        return accRenderTaskPtr()->accDrawDataAs<DrawData>().color;
    }

    inline void PgonRenderable::setColor(const Colorf& clr) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().color = clr;
    }

    inline void PgonRenderable::onBeforeDraw(Shader& s) {
        SimpleColorShader& scs = (SimpleColorShader&)s;
        scs.setUniforms(accRenderTaskPtr()->getDrawDataAs<DrawData>());
    }
}