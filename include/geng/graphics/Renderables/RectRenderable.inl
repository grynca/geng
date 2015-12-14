#include "RectRenderable.h"
#include "../Window.h"
#include "../Shaders/RectShader.h"
#include "../VertexData/VertexDataP.h"
#include "../geom_factories.h"


namespace grynca {

    template <typename GameType>
    inline RectRenderable::RectRenderable(GameType& game) {
        color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
        Window& window = game.template getModule<Window>();

        FactoryRectTF<VertexDataP::Vertex> fact = window.getVertices().get<VertexDataP>().addWithFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        Renderable::init<RectShader, VertexDataP>(fact.getGeom());
    }

    inline Vec2 RectRenderable::getSize()const {
        return local_transform_.getScale();
    }

    inline Vec2 RectRenderable::getOffset()const {
        const FactoryRectTF<VertexDataP::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        return fact.getOffset(0);
    }

    inline void RectRenderable::getColor(float* c)const {
        memcpy(c, color_, sizeof(float)*4);
    }

    inline RectRenderable& RectRenderable::setColor(float r, float g, float b, float a) {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
        return *this;
    }
    
    inline RectRenderable& RectRenderable::setSize(const Vec2& size) {
        local_transform_.setScale(size);
        return *this;
    }

    inline RectRenderable& RectRenderable::setOffset(const Vec2& offset) {
        FactoryRectTF<VertexDataP::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.setOffset(0, offset);
        return *this;
    }


    inline void RectRenderable::preRender() {
        RectShader& rs = (RectShader&)getShader();

        rs.setUniformMat3(rs.u_transform, mvp_);
        rs.setUniform1f(rs.u_z_coord, layer_z_);
        rs.setUniform4fv(rs.u_color, color_, 1);
    }
}