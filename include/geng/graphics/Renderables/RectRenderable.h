#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "RenderableBase.h"

namespace grynca {

    // fw
    struct Color;

    class RectRenderable : public RenderableBase {
    public:
        RectRenderable();

        template <typename GameType>
        RectRenderable& init(GameType& game);       // creates rect geom (size[1,1], offset[-0.5, -0.5])
        template <typename GameType>
        RectRenderable& init(GameType& game, Geom& geom);       // reuses existing geom

        Vec2 getSize()const;
        Vec2 getGeomNormOffset()const;
        Colorf getColor()const;

        RectRenderable& setColor(const Colorf& clr);
        RectRenderable& setSize(const Vec2& size);      // changes local transform scale
        RectRenderable& setGeomNormOffset(const Vec2& offset);      // normalized to size

        virtual void setUniforms(const Mat3& mvp, Shader& s) override;
    protected:
        Colorf color_;
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
