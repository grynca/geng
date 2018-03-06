#include "RectBorderRenderable.h"
#include "../Shaders/RectBorderShader.h"

namespace grynca {

    inline void RectBorderRenderable::setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint) {
        RectRenderable::setNewGeom(norm_offset, usage_hint);
        accRenderTaskPtr()->accDrawDataAs<DrawData>().offset = norm_offset;
    }

    inline void RectBorderRenderable::setStaticSharedQuadGeom(NormOffset::Type offset_type) {
        PgonRenderable::setStaticSharedQuadGeom(offset_type);
        accRenderTaskPtr()->accDrawDataAs<DrawData>().offset = NormOffset::get(offset_type);
    }

    inline Vec2 RectBorderRenderable::getNormBorders()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().borders;
    }

    inline Vec2 RectBorderRenderable::getBordersPx()const {
        Vec2 size = getSize();
        Vec2 borders = getRenderTaskPtr()->getDrawDataAs<DrawData>().borders;
        return borders*size;
    }

    inline Vec2 RectBorderRenderable::getGeomNormOffset() {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().offset;
    }

    inline void RectBorderRenderable::setColor(const Colorf& clr) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().color = clr;
    }

    inline void RectBorderRenderable::setGeomNormOffset(const Vec2& offset) {
        RectRenderable::setGeomNormOffset(offset);
        accRenderTaskPtr()->accDrawDataAs<DrawData>().offset = offset;
    }

    inline void RectBorderRenderable::setNormBorders(Vec2 borders) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().borders = borders;
    }

    inline void RectBorderRenderable::setSize(const Vec2& size, bool scale_borders) {
        if (!scale_borders) {
            // keep borders' size
            DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
            dd.borders *= getSize()/size;
        }
        RectRenderable::setSize(size);
    }

    inline void RectBorderRenderable::setBordersPx(Vec2 borders_px) {
        Vec2 size = getSize();
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.borders = borders_px/size;
    }

    inline void RectBorderRenderable::onBeforeDraw(Shader& s) {
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.transform *= Mat3::createScaleT(dd.size);

        RectBorderShader& rbs = (RectBorderShader&)s;
        rbs.setUniforms(dd);
    }
}