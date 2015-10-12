#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    class RectRenderable : public Renderable {
    public:
        RectRenderable();

        template <typename GameType>
        RectRenderable& init(GameType& game, uint32_t layer_id, const Vec2& size);
        template <typename GameType>
        RectRenderable& init(GameType& game, uint32_t layer_id, const Vec2& size, const Vec2& offset);


        virtual void preRender() override ;

        void setColor(float r, float g, float b, float a = 1.0f);
        Vec2 getSize();
        Vec2 getOffset();
        void setSize(const Vec2& size);
        void setOffset(const Vec2& offset);
    private:
        float color_[4];
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
