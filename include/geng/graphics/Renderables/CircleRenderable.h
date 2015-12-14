#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    class CircleRenderable : public Renderable {
    public:
        template <typename GameType>
        CircleRenderable(GameType& game, float radius, float inner_radius = 0.0f);

        float getInnerRadius()const;
        float getOuterRadius()const;
        void getColor(float* c)const;


        CircleRenderable& setColor(float r, float g, float b, float a = 1.0f) ;
        CircleRenderable& setInnerRadius(float inner_r);
        CircleRenderable& setOuterRadius(float outer_r);

        virtual void preRender() override ;
    private:
        float color_[4];
        float inner_radius_;
        float outer_radius_;
    };
}

#include "CircleRenderable.inl"
#endif //CIRCLERENDERABLE_H
