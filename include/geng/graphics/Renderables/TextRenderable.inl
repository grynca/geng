#include "TextRenderable.h"
#include "../Shaders/TextShader.h"
#include "../VertexData/VertexDataPT.h"
#include "geng/graphics/VertexData/GeomStates/GeomStateText.h"

namespace grynca {

    inline TextRenderable::TextRenderable()
     : dirty_text_state_(false)
    {}

    inline TextRenderable::~TextRenderable() {
        if (dirty_text_state_) {
            // cache texture id to draw data for faster drawing
            accRenderTaskPtr()->accDrawDataAs<DrawData>().texture_id = getTextState().getFontPack()->getTextureId();
        }
    }

    inline void TextRenderable::setNewGeom(GeomUsageHint usage_hint) {
        VertexDataPT& verts = accWindow().getVertices().getFast<VertexDataPT>();
        Geom& geom = verts.addItem(GL_TRIANGLES, usage_hint);
        geom.setState(GeomStateType::gstText);
        setGeom(geom);
    }

    inline const GeomStateText& TextRenderable::getTextState()const {
        const Geom& geom = getRenderTaskPtr()->getGeom().get();
        ASSERT(geom.getStateType() == GeomStateType::gstText);
        return (GeomStateText&)(geom.getState());
    }

    inline Colorf TextRenderable::getColor()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().color;
    }

    inline Colorf& TextRenderable::accColor() {
        return accRenderTaskPtr()->accDrawDataAs<DrawData>().color;
    }

    inline GeomStateText& TextRenderable::accTextState() {
        dirty_text_state_ = true;
        Geom& geom = accRenderTaskPtr()->accGeom().acc();
        ASSERT(geom.getStateType() == GeomStateType::gstText);
        return (GeomStateText&)(geom.accState());
    }

    inline void TextRenderable::setColor(const Colorf& clr) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().color = clr;
    }

    inline void TextRenderable::onBeforeDraw(Shader& s) {
        TextShader& ts = (TextShader&)s;
        ts.setUniforms(accRenderTaskPtr()->accDrawDataAs<DrawData>());
    }
}