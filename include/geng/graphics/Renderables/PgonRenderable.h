#ifndef POLYGONRENDERABLE_H
#define POLYGONRENDERABLE_H

#include "RenderableBase.h"

namespace grynca {

    // Convex polygon
    class PgonRenderable : public RenderableBase {
    public:
        PgonRenderable();

        template <typename GameType>
        PgonRenderable& init(GameType& game);                // with new empty geom

        template <typename GameType>
        PgonRenderable& init(GameType& game, Geom& geom);        // with shared geom

        Colorf getColor()const;
        PgonRenderable& setColor(const Colorf& clr);

        virtual void setUniforms(const Mat3& mvp, Shader& s);
    protected:
        Colorf color_;
    };

}

#include "PgonRenderable.inl"
#endif //POLYGONRENDERABLE_H
