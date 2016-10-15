#include "RectRenderable.h"
#include "geng/graphics/VertexData/Factories/geom_factories.h"

namespace grynca {

    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game) {
        Window& window = game.template getModule<Window>();
        FactoryRectTF<VertexDataP::Vertex> fact = window.getVertices().get<VertexDataP>().addWithFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        PgonRenderable::init(game, fact.getGeom());
        return *this;
    }

    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game, Geom& geom) {
        PgonRenderable::init(game, geom);
        return *this;
    }

    inline Vec2 RectRenderable::getSize()const {
        return local_transform_.getScale();
    }

    inline Vec2 RectRenderable::getGeomNormOffset()const {
        const FactoryRectTF<VertexDataP::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        return fact.getOffset(0);
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
}