#include "ImageRenderable.h"
#include "../Window.h"
#include "../Shaders/SpriteShader.h"
#include "../VertexData/VertexDataPT.h"

namespace grynca {

    inline ImageRenderable::ImageRenderable()
     : texture_unit_(0)
    {}

    template <typename GameType>
    inline ImageRenderable& ImageRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const TextureRegion& tr) {
        return init(game, layer_id, texture_unit, tr.getTextureRect(), tr.getRect().getSize(), tr.getRect().getSize()/-2);
    }

    template <typename GameType>
    inline ImageRenderable& ImageRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const ARect& texture_coords, const Vec2& size) {
        return init(game, layer_id, texture_unit, texture_coords, size, size/-2);
    }

    template <typename GameType>
    inline ImageRenderable& ImageRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, const ARect& texture_coords, const Vec2& size, const Vec2& offset) {
        texture_unit = texture_unit_;
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLE_FAN);
        geom_utils::RectTF::add<VertexDataPT::Vertex>(geom);
        geom_utils::RectTF::setSize<VertexDataPT::Vertex>(geom, 0, size);
        geom_utils::RectTF::setOffset<VertexDataPT::Vertex>(geom, 0, offset);
        geom_utils::RectTF::setTC<VertexDataPT::Vertex>(geom, 0, texture_coords.getLeftTop(), texture_coords.getRightBot());
        Renderable::init<SpriteShader, VertexDataPT>(geom, layer_id);
        return *this;
    }

    inline void ImageRenderable::preRender() {
        SpriteShader& ss = (SpriteShader&)getShader();

        ss.setUniformMat3(ss.u_transform, mvp_);
        ss.setUniform1f(ss.u_z_coord, layer_z_);
        ss.setUniform1i(ss.u_texture, texture_unit_);
    }

    inline uint32_t ImageRenderable::getTextureUnit()const {
        return texture_unit_;
    }

    inline void ImageRenderable::setTextureUnit(uint32_t tid) {
        texture_unit_ = tid;
    }

    inline void ImageRenderable::setTextureCoords(const ARect& tc) {
        geom_utils::RectTF::setTC<VertexDataPT::Vertex>(getGeom(), 0, tc.getLeftTop(), tc.getRightBot());
    }

    inline Vec2 ImageRenderable::getSize() {
        return geom_utils::RectTF::getSize<VertexDataPT::Vertex>(getGeom(), 0);
    }

    inline Vec2 ImageRenderable::getOffset() {
        return geom_utils::RectTF::getOffset<VertexDataPT::Vertex>(getGeom(), 0);
    }

    inline void ImageRenderable::setSize(const Vec2& size) {
        geom_utils::RectTF::setSize<VertexDataPT::Vertex>(getGeom(), 0, size);
    }

    inline void ImageRenderable::setOffset(const Vec2& offset) {
        geom_utils::RectTF::setOffset<VertexDataPT::Vertex>(getGeom(), 0, offset);
    }

}