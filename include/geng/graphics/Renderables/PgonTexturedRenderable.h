#ifndef PGONTEXTUREDRENDERABLE_H
#define PGONTEXTUREDRENDERABLE_H

#include "RenderableBase.h"

namespace grynca {

    // TODO: SpriteRenderable bude dedit z tohodle
    //       otestovat tohle
    //       zamyslet se nad nejakym toolem kterym budu delat UVcka z texture atlasu ( nebo si udelat vlastni )
    class PgonTexturedRenderable : public RenderableBase {
    public:
        PgonTexturedRenderable();

        template <typename GameType>
        PgonTexturedRenderable& init(GameType& game);                // with new empty geom

        template <typename GameType>
        PgonTexturedRenderable& init(GameType& game, Geom& geom);        // with shared geom

        PgonTexturedRenderable& setTextureUnit(uint32_t tid);
        uint32_t getTextureUnit()const;

        virtual void setUniforms(const Mat3& mvp, Shader& s);
    protected:
        uint32_t texture_unit_;
    };

};

#include "PgonTexturedRenderable.inl"
#endif //PGONTEXTUREDRENDERABLE_H
