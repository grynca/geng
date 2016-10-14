#include "RectBorderRenderable.h"
#include "../Shaders/RectBorderShader.h"
#include "assets/Image.h"

namespace grynca {

    inline RectBorderRenderable::RectBorderRenderable()
     : borders_(0.5f, 0.5f), offset_(-0.5f, -0.5f)
    {
    }

    template <typename GameType>
    inline RectBorderRenderable& RectBorderRenderable::init(GameType& game) {
        RectRenderable::init(game);
        setShader<RectBorderShader>();
        offset_ = RectRenderable::getGeomNormOffset();
        return *this;
    }

    inline RectBorderRenderable& RectBorderRenderable::setSize(const Vec2& size) {
        Vec2 borders_px = getBorders();
        RectRenderable::setSize(size);
        setBorders(borders_px);
        return *this;
    }

    inline RectBorderRenderable& RectBorderRenderable::setColor(const Colorf& clr) {
        return (RectBorderRenderable&)RectRenderable::setColor(clr);
    }

    inline RectBorderRenderable& RectBorderRenderable::setGeomNormOffset(const Vec2& offset) {
        offset_ = offset;
        return (RectBorderRenderable&)RectRenderable::setGeomNormOffset(offset);
    }

    inline RectBorderRenderable& RectBorderRenderable::setBorders(Vec2 bs) {
        Vec2 size = getSize();
        borders_ = bs/size;
        return *this;
    }

    inline Vec2 RectBorderRenderable::getBorders() {
        Vec2 size = getSize();
        return borders_*size;
    }

    inline void RectBorderRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        RectBorderShader& rbs = (RectBorderShader&)s;

        rbs.setUniformMat3(rbs.u_transform, mvp);
        rbs.setUniform1f(rbs.u_z_coord, layer_z_);
        rbs.setUniform4fv(rbs.u_color, color_.c_, 1);
        rbs.setUniform2f(rbs.u_borders, borders_);
        rbs.setUniform2f(rbs.u_offset, offset_);
    }

}