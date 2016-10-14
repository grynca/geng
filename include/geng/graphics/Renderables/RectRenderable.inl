#include "RectRenderable.h"
#include "../Window.h"
#include "../Shaders/RectShader.h"
#include "../VertexData/VertexDataP.h"
#include "../geom_factories.h"
#include "assets/Image.h"


namespace grynca {

    inline RectRenderable::RectRenderable()
     : color_(Colorf::White())
    {
    }

    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game) {
        Window& window = game.template getModule<Window>();

        FactoryRectTF<VertexDataP::Vertex> fact = window.getVertices().get<VertexDataP>().addWithFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        RenderableBase::init<RectShader, VertexDataP>(fact.getGeom());
        return *this;
    }

    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game, Geom& geom) {
        Window& window = game.template getModule<Window>();

        RenderableBase::init<RectShader, VertexDataP>(geom);
        return *this;
    }

    inline Vec2 RectRenderable::getSize()const {
        return local_transform_.getScale();
    }

    inline Vec2 RectRenderable::getGeomNormOffset()const {
        const FactoryRectTF<VertexDataP::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        return fact.getOffset(0);
    }

    inline Colorf RectRenderable::getColor()const {
        return color_;
    }

    inline RectRenderable& RectRenderable::setColor(const Colorf& clr) {
        color_ = clr;
        return *this;
    }
    
    inline RectRenderable& RectRenderable::setSize(const Vec2& size) {
        local_transform_.setScale(size);
        return *this;
    }

    inline RectRenderable& RectRenderable::setGeomNormOffset(const Vec2& offset) {
        FactoryRectTF<VertexDataP::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.setOffset(0, offset);
        return *this;
    }


    inline void RectRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        RectShader& rs = (RectShader&)s;

        rs.setUniformMat3(rs.u_transform, mvp);
        rs.setUniform1f(rs.u_z_coord, layer_z_);
        rs.setUniform4fv(rs.u_color, color_.c_, 1);
    }
}