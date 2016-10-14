#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "RenderableBase.h"

namespace grynca {

    class CircleRenderable : public RenderableBase {
    public:
        CircleRenderable();
        template <typename GameType>
        CircleRenderable& init(GameType& game, float radius, float inner_radius = 0.0f);

        float getInnerRadius()const;
        float getOuterRadius()const;
        Colorf getColor()const;


        CircleRenderable& setColor(const Colorf& c) ;
        CircleRenderable& setInnerRadius(float inner_r);
        CircleRenderable& setOuterRadius(float outer_r);

        virtual void setUniforms(const Mat3& mvp, Shader& s) override;

        // uses shared geom which is read only
        const Geom& getGeom()const { return RenderableBase::getGeom(); }
    private:
        Colorf color_;
        float inner_radius_;
        float outer_radius_;
    };
}

#include "CircleRenderable.inl"
#endif //CIRCLERENDERABLE_H
