#ifndef RECTBORDERRENDERABLE_H
#define RECTBORDERRENDERABLE_H

#include "RectRenderable.h"

namespace grynca {

    //fw
    struct Color;

    class RectBorderRenderable : public RectRenderable {
    public:
        RectBorderRenderable();

        template <typename GameType>
        RectBorderRenderable& init(GameType& game);

        RectBorderRenderable& setColor(const Colorf& clr);
        RectBorderRenderable& setGeomNormOffset(const Vec2& offset);
        RectBorderRenderable& setSize(const Vec2& size);        // changes transform scale
        RectBorderRenderable& setBorders(Vec2 bs);
        Vec2 getBorders();

        virtual void setUniforms(const Mat3& mvp, Shader& s) override;
    private:
        Vec2 borders_;
        Vec2 offset_;
    };
}

#include "RectBorderRenderable.inl"
#endif //RECTBORDERRENDERABLE_H
