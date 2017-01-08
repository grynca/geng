#include "TextRenderable.h"
#include "../Shaders/TextShader.h"
#include "../VertexData/VertexDataPT.h"
#include "../VertexData/TextStates.h"

namespace grynca {

    inline VertexData::ItemRef TextRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataPT& verts = w.getVertices().get<VertexDataPT>();
        Geom& geom = verts.addItem(GL_TRIANGLES, GeomState::stText, usage_hint);
        return geom;
    }

    inline const TextState& TextRenderable::getTextState()const {
        VertexDataPT& verts = getWindow().getVertices().get<VertexDataPT>();
        Geom& geom = const_cast<TextRenderable *>(this)->getRenderTask()->getGeom().get();

        return verts.getTextStates().getItem(geom.getGeomStateId());
    }

    inline Colorf TextRenderable::getColor()const {
        return getRenderTask()->getUniformsAs<TextShader::Uniforms>().color;
    }

    inline u32 TextRenderable::getTextureUnit()const {
        return getRenderTask()->getUniformsAs<TextShader::Uniforms>().texture;
    }

    inline Colorf& TextRenderable::accColor() {
        return accRenderTask()->getUniformsAs<TextShader::Uniforms>().color;
    }

    inline TextState& TextRenderable::accTextState() {
        VertexDataPT& verts = getWindow().getVertices().get<VertexDataPT>();
        Geom& geom = getRenderTask()->getGeom().get();
        return verts.getTextStates().getItem(geom.getGeomStateId());
    }

    inline TextRenderable& TextRenderable::setColor(const Colorf& clr) {
        accRenderTask()->getUniformsAs<TextShader::Uniforms>().color = clr;
        return *this;
    }

    inline TextRenderable& TextRenderable::setTextureUnit(u32 tid) {
        accRenderTask()->getUniformsAs<TextShader::Uniforms>().texture = tid;
        return *this;
    }

    inline TextRenderable& TextRenderable::setPosition(const Vec2& pos) {
        accRenderTask()->accLocalTransform().setPosition(pos);
        return *this;
    }

    inline Vec2 TextRenderable::calcBoundSize() {
        Geom& geom = getRenderTask()->getGeom().get();
        VertexDataPT& verts = getWindow().getVertices().get<VertexDataPT>();
        TextState& ts = verts.getTextStates().getItem(geom.getGeomStateId());

        u32 vertices_cnt = ts.getTextSize()*6;   // 6 verts per character

        Vec2 left_top = geom.getVertex<VertexDataPT::Vertex>(1).pos;
        Vec2 right_bot = geom.getVertex<VertexDataPT::Vertex>(vertices_cnt-3).pos;
        return (right_bot - left_top)*accRenderTask()->accLocalTransform().getScale();
    }
}