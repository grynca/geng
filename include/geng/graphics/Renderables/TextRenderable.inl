#include "TextRenderable.h"
#include "assets.h"
#include "../Shaders/TextShader.h"
#include "../VertexData/VertexDataPT.h"


namespace grynca {

    inline TextRenderable::TextRenderable()
        : assets_(NULL), texture_unit_(0), font_pack_id_(uint32_t(-1)), font_size_(-1)
    {
        color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
    }

    template <typename GameType>
    inline TextRenderable& TextRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t font_pack_id, uint32_t font_size, const std::string& text) {
        assets_ = & game.template getModule<AssetsManager>();
        texture_unit_ = texture_unit;
        font_pack_id_ = font_pack_id;
        font_size_ = font_size;
        text_ = text;
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLES);
        Renderable::init<TextShader, VertexDataPT>(geom, layer_id);
        updateTextGeom_();
        return *this;
    }

    inline AssetsManager& TextRenderable::getAssets() {
        return *assets_;
    }

    inline void TextRenderable::preRender() {
        TextShader& ts = (TextShader&)getShader();

        ts.setUniformMat3(ts.u_transform, mvp_);
        ts.setUniform1f(ts.u_z_coord, layer_z_);
        ts.setUniform1i(ts.u_texture, texture_unit_);
        ts.setUniform4fv(ts.u_color, color_, 1);
    }

    inline void TextRenderable::setFont(uint32_t font_pack_id) {
        font_pack_id_  = font_pack_id;
        updateTextGeom_();
    }

    inline void TextRenderable::setFont(uint32_t font_pack_id, uint32_t font_size) {
        font_pack_id_ = font_pack_id;
        font_size_ = font_size;
        updateTextGeom_();
    }

    inline void TextRenderable::setFontSize(uint32_t font_size) {
        font_size_ = font_size;
        updateTextGeom_();
    }

    inline void TextRenderable::setText(const std::string& t) {
        text_ = t;
        updateTextGeom_();
    }

    inline const std::string& TextRenderable::getText()const {
        return text_;
    }

    inline const uint32_t TextRenderable::getFontSize()const {
        return font_size_;
    }

    inline const uint32_t TextRenderable::getFontPackId()const {
        return font_pack_id_;
    }

    inline void TextRenderable::setColor(float r, float g, float b, float a) {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
    }

    inline Vec2 TextRenderable::getSize() {
        Geom& geom = getGeom();
        uint32_t last_char_vert_offset = uint32_t(text_.size()-1)*6;
        Vec2 lt = geom_utils::RectT::getLeftTop<VertexDataPT::Vertex>(geom, 0);
        Vec2 rb = geom_utils::RectT::getRightBot<VertexDataPT::Vertex>(geom, last_char_vert_offset);
        return rb-lt;
    }

    inline void TextRenderable::updateTextGeom_() {
        Geom& geom = getGeom();
        geom.removeAllVertices<VertexDataPT::Vertex>();
        FontPack& fp = assets_->getFontsPacks().getItem(font_pack_id_);
        const SizedFont& font = fp.getFont().getSizedFont(font_size_);
        float xpos = 0;
        for (uint32_t i=0; i<text_.size(); ++i) {
            const Glyph& g = font.getGlyph(text_[i]);
            const TextureRegion& tex_r = g.getRegion();

            uint32_t start_vert = geom_utils::RectT::add<VertexDataPT::Vertex>(geom);
            Vec2 offset(xpos+g.getOffsetX(), -g.getOffsetY());
            geom_utils::RectT::setSize<VertexDataPT::Vertex>(geom, start_vert, tex_r.getRect().getSize());
            geom_utils::RectT::setOffset<VertexDataPT::Vertex>(geom, start_vert, offset);
            geom_utils::RectT::setTC<VertexDataPT::Vertex>(geom, start_vert, tex_r.getTextureRect().getLeftTop(), tex_r.getTextureRect().getRightBot());
            xpos += g.getAdvanceX();
        }
    }

}