#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "PgonRenderable.h"

namespace grynca {

    // fw
    struct Color;

    class RectRenderable : public PgonRenderable {
    public:
        template <typename GameType>
        RectRenderable& init(GameType& game);       // creates rect geom (size[1,1], offset[-0.5, -0.5])
        template <typename GameType>
        RectRenderable& init(GameType& game, Geom& geom);       // reuses existing geom

        Vec2 getSize()const;
        Vec2 getGeomNormOffset()const;

        RectRenderable& setSize(const Vec2& size);      // changes local transform scale
        RectRenderable& setGeomNormOffset(const Vec2& offset);      // normalized to size
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
