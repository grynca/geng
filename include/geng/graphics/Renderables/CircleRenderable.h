#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "../Renderable.h"
#include "../Window.h"
#include "../Shaders.h"
#include "../Vertices.h"
#include "maths/shapes/Circle.h"
#include "../VertexData/VertexDataP.h"
#include "../Shaders/CircleShader.h"
#include <cassert>

namespace grynca {

    class CircleRenderable : public Renderable {
    public:
        CircleRenderable(Window& window, uint32_t layer_id, float radius, float inner_radius = 0.0f)
         : Renderable(window), inner_radius_(inner_radius), outer_radius_(radius)
        {
            color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
            Geom& g = window.getVertices().get<VertexDataP>().getUnitQuadGeom();
            init<CircleShader, VertexDataP>(g, layer_id);
        }

        virtual void preRender() override {
            CircleShader& cs = (CircleShader&)getShader();

            cs.setUniformMat3(cs.u_transform, mvp_);
            cs.setUniform1f(cs.u_z_coord, layer_z_);
            cs.setUniform2f(cs.u_r_range, {inner_radius_, outer_radius_} );
            cs.setUniform4fv(cs.u_color, color_, 1);
        }

        void setColor(float r, float g, float b, float a = 1.0f) {
            color_[0] = r;
            color_[1] = g;
            color_[2] = b;
            color_[3] = a;
        }

        float getInnerRadius() { return inner_radius_; }
        void setInnerRadius(float inner_r) { inner_radius_ = inner_r; }
        float getOuterRadius() { return outer_radius_; }
        void setOuterRadius(float outer_r) { outer_radius_ = outer_r; }

    private:
        float color_[4];
        float inner_radius_;
        float outer_radius_;
    };
}

#endif //CIRCLERENDERABLE_H
