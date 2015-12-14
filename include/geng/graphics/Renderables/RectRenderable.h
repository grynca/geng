#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    class RectRenderable : public Renderable {
    public:
        template <typename GameType>
        RectRenderable(GameType& game);

        Vec2 getSize()const;
        Vec2 getOffset()const;
        void getColor(float* c)const;

        RectRenderable& setColor(float r, float g, float b, float a = 1.0f);
        RectRenderable& setSize(const Vec2& size);
        RectRenderable& setOffset(const Vec2& offset);


        virtual void preRender() override ;
    private:
        float color_[4];
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
