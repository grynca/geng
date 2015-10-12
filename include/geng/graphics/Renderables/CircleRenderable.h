#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    class CircleRenderable : public Renderable {
    public:
        CircleRenderable();

        template <typename GameType>
        CircleRenderable& init(GameType& game, uint32_t layer_id, float radius, float inner_radius = 0.0f);

        virtual void preRender() override ;

        void setColor(float r, float g, float b, float a = 1.0f) ;
        float getInnerRadius();
        float getOuterRadius();
        void setInnerRadius(float inner_r);
        void setOuterRadius(float outer_r);

    private:
        float color_[4];
        float inner_radius_;
        float outer_radius_;
    };
}

#include "CircleRenderable.inl"
#endif //CIRCLERENDERABLE_H
