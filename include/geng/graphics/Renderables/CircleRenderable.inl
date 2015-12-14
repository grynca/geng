#include "CircleRenderable.h"
#include "../Window.h"
#include "../Vertices.h"
#include "../VertexData/VertexDataP.h"
#include "../Shaders/CircleShader.h"


namespace grynca {

    template <typename GameType>
    inline CircleRenderable::CircleRenderable(GameType& game, float radius, float inner_radius)
     : inner_radius_(inner_radius), outer_radius_(radius)
    {
        color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataP>().getUnitQuadGeom();
        Renderable::init<CircleShader, VertexDataP>(geom);
    }

    inline float CircleRenderable::getInnerRadius()const {
        return inner_radius_;
    }

    inline float CircleRenderable::getOuterRadius()const {
        return outer_radius_;
    }

    inline void CircleRenderable::getColor(float* c)const {
        memcpy(c, color_, sizeof(float)*4);
    }

    inline CircleRenderable& CircleRenderable::setColor(float r, float g, float b, float a) {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
        return *this;
    }

    inline CircleRenderable& CircleRenderable::setInnerRadius(float inner_r) {
        inner_radius_ = inner_r;
        return *this;
    }

    inline CircleRenderable& CircleRenderable::setOuterRadius(float outer_r) {
        outer_radius_ = outer_r;
        return *this;
    }

    inline void CircleRenderable::preRender() {
        CircleShader& cs = (CircleShader&)getShader();

        cs.setUniformMat3(cs.u_transform, mvp_);
        cs.setUniform1f(cs.u_z_coord, layer_z_);
        cs.setUniform2f(cs.u_r_range, {inner_radius_, outer_radius_} );
        cs.setUniform4fv(cs.u_color, color_, 1);
    }
}