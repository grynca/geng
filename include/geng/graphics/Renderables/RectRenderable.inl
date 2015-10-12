#include "RectRenderable.h"
#include "../Window.h"
#include "../Shaders/RectShader.h"
#include "../VertexData/VertexDataP.h"
#include "../geom_utils.h"


namespace grynca {

    inline RectRenderable::RectRenderable()
    {
        color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
    }


    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game, uint32_t layer_id, const Vec2& size) {
        return init(game, layer_id, size, size/-2);
    }

    template <typename GameType>
    inline RectRenderable& RectRenderable::init(GameType& game, uint32_t layer_id, const Vec2& size, const Vec2& offset) {
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataP>().addItem(GL_TRIANGLE_FAN);
        geom_utils::RectTF::add<VertexDataP::Vertex>(geom);
        geom_utils::RectTF::setSize<VertexDataP::Vertex>(geom, 0, size);
        geom_utils::RectTF::setOffset<VertexDataP::Vertex>(geom, 0, offset);
        Renderable::init<RectShader, VertexDataP>(geom, layer_id);
        return *this;
    }


    inline void RectRenderable::preRender() {
        RectShader& rs = (RectShader&)getShader();

        rs.setUniformMat3(rs.u_transform, mvp_);
        rs.setUniform1f(rs.u_z_coord, layer_z_);
        rs.setUniform4fv(rs.u_color, color_, 1);
    }

    inline void RectRenderable::setColor(float r, float g, float b, float a) {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
    }

    inline Vec2 RectRenderable::getSize() {
        return geom_utils::RectTF::getSize<VertexDataP::Vertex>(getGeom(), 0);
    }

    inline Vec2 RectRenderable::getOffset() {
        return geom_utils::RectTF::getOffset<VertexDataP::Vertex>(getGeom(), 0);
    }
    
    inline void RectRenderable::setSize(const Vec2& size) {
        geom_utils::RectTF::setSize<VertexDataP::Vertex>(getGeom(), 0, size);
    }

    inline void RectRenderable::setOffset(const Vec2& offset) {
        geom_utils::RectTF::setOffset<VertexDataP::Vertex>(getGeom(), 0, offset);
    }

}