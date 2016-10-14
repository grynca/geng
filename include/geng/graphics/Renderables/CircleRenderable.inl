#include "CircleRenderable.h"
#include "../Window.h"
#include "../Vertices.h"
#include "../VertexData/VertexDataP.h"
#include "../Shaders/CircleShader.h"


namespace grynca {

    inline CircleRenderable::CircleRenderable()
     : inner_radius_(0.0f), outer_radius_(0.0f)
    {
    }

    template <typename GameType>
    inline CircleRenderable& CircleRenderable::init(GameType& game, float radius, float inner_radius) {
        inner_radius_ = inner_radius;
        outer_radius_ = radius;
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataP>().getUnitQuadGeom();
        RenderableBase::init<CircleShader, VertexDataP>(geom);
        return *this;
    }

    inline float CircleRenderable::getInnerRadius()const {
        return inner_radius_;
    }

    inline float CircleRenderable::getOuterRadius()const {
        return outer_radius_;
    }

    inline Colorf CircleRenderable::getColor()const {
        return color_;
    }

    inline CircleRenderable& CircleRenderable::setColor(const Colorf& c) {
        color_ = c;
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

    inline void CircleRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        CircleShader& cs = (CircleShader&)s;

        cs.setUniformMat3(cs.u_transform, mvp);
        cs.setUniform1f(cs.u_z_coord, layer_z_);
        cs.setUniform2f(cs.u_r_range, {inner_radius_, outer_radius_} );
        cs.setUniform4fv(cs.u_color, color_.c_, 1);
    }
}