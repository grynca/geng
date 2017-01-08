#include "RectBorderRenderable.h"
#include "../Shaders/RectBorderShader.h"

namespace grynca {

    inline VertexData::ItemRef RectBorderRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        return RectRenderable::createNewGeom(w, usage_hint);
    }

    inline Vec2 RectBorderRenderable::getBorders()const {
        Vec2 size = getSize();
        Vec2 borders = getRenderTask()->getUniformsAs<RectBorderShader::Uniforms>().borders;
        return borders*size;
    }

    inline Vec2 RectBorderRenderable::getGeomNormOffset() {
        return getRenderTask()->getUniformsAs<RectBorderShader::Uniforms>().offset;
    }

    inline RectBorderRenderable& RectBorderRenderable::setColor(const Colorf& clr) {
        accRenderTask()->getUniformsAs<RectBorderShader::Uniforms>().color = clr;
        return *this;
    }

    inline RectBorderRenderable& RectBorderRenderable::setSize(const Vec2& size) {
        Vec2 borders_px = getBorders();
        RectRenderable::setSize(size);
        RectBorderShader::Uniforms& unis = accRenderTask()->getUniformsAs<RectBorderShader::Uniforms>();
        unis.borders = borders_px/size;
        return *this;
    }

    inline RectBorderRenderable& RectBorderRenderable::setGeomNormOffset(const Vec2& offset) {
        RectRenderable::setGeomNormOffset(offset);
        accRenderTask()->getUniformsAs<RectBorderShader::Uniforms>().offset = offset;
        return *this;
    }

    inline RectBorderRenderable& RectBorderRenderable::setBorders(Vec2 borders_px) {
        Vec2 size = getSize();
        RectBorderShader::Uniforms& unis = accRenderTask()->getUniformsAs<RectBorderShader::Uniforms>();
        unis.borders = borders_px/size;
        return *this;
    }
}