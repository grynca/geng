#ifndef IMAGERENDERABLE_H
#define IMAGERENDERABLE_H

#include "../Renderable.h"
#include "assets/TexturePacker.h"

namespace grynca {

    class ImageRenderable : public Renderable {
    public:
        ImageRenderable();

        template <typename GameType>
        ImageRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const TextureRegion& tr);
        template <typename GameType>
        ImageRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const ARect& texture_coords, const Vec2& size) ;
        template <typename GameType>
        ImageRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const ARect& texture_coords, const Vec2& size, const Vec2& offset);

        virtual void preRender() override ;

        uint32_t getTextureUnit()const;
        void setTextureUnit(uint32_t tid);
        void setTextureCoords(const ARect& tc);

        Vec2 getSize() ;
        Vec2 getOffset() ;
        void setSize(const Vec2& size);
        void setOffset(const Vec2& offset);
    private:
        uint32_t texture_unit_;
    };

}

#include "ImageRenderable.inl"
#endif //IMAGERENDERABLE_H
