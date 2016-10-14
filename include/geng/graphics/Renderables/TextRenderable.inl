#include "TextRenderable.h"
#include "assets.h"
#include "../Shaders/TextShader.h"
#include "../VertexData/VertexDataPT.h"
#include "../geom_factories.h"


namespace grynca {


    inline TextRenderable::Setter::~Setter() {
        tr_->updateTextGeom_();
    }

    inline TextRenderable::Setter& TextRenderable::Setter::setFont(Index font_pack_id) {
        tr_->font_pack_id_ = font_pack_id;
        return *this;
    }

    inline TextRenderable::Setter& TextRenderable::Setter::setFontSize(uint32_t font_size) {
        tr_->font_size_ = font_size;
        return *this;
    }

    inline TextRenderable::Setter& TextRenderable::Setter::setText(const std::string& t) {
        tr_->text_ = t;
        return *this;
    }

    inline TextRenderable::Setter::Setter(TextRenderable& tr)
     : tr_(&tr)
    {}

    inline TextRenderable::TextRenderable()
        : assets_(NULL), texture_unit_(0), font_pack_id_(Index::Invalid()), font_size_(-1)
    {
        color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
    }

    template <typename GameType>
    inline TextRenderable& TextRenderable::init(GameType& game) {
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLES);
        init(game, geom);
        return *this;
    }

    template <typename GameType>
    inline TextRenderable& TextRenderable::init(GameType& game, Geom& geom) {
        assets_ = &game.template getModule<AssetsManager>();
        RenderableBase::init<TextShader, VertexDataPT>(geom);
        return *this;
    }

    inline AssetsManager& TextRenderable::getAssets()const {
        return *assets_;
    }

    inline const std::string& TextRenderable::getText()const {
        return text_;
    }

    inline uint32_t TextRenderable::getFontSize()const {
        return font_size_;
    }

    inline Index TextRenderable::getFontPackId()const {
        return font_pack_id_;
    }

    inline void TextRenderable::getColor(float* c)const {
        memcpy(c, color_, sizeof(float)*4);
    }

    inline uint32_t TextRenderable::getTextureUnit()const {
        return texture_unit_;
    }

    inline TextRenderable& TextRenderable::setColor(float r, float g, float b, float a) {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
        return *this;
    }

    inline TextRenderable& TextRenderable::updateTextGeom_() {
        Geom& geom = getGeom();
        geom.removeAllVertices();
        FontPack& fp = assets_->getFontsPacks().getItem(font_pack_id_);
        const SizedFont& font = fp.getFont().getSizedFont(font_size_);
        float xpos = 0;
        FactoryRectT<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectT<VertexDataPT::Vertex> >();
        for (uint32_t i=0; i<text_.size(); ++i) {
            const Glyph& g = font.getGlyph(text_[i]);
            const TextureRegion& tex_r = g.getRegion();

            Vec2 offset(xpos+g.getOffsetX(), -g.getOffsetY());
            uint32_t start_vert = fact.add(tex_r.getRect().getSize(), offset);
            fact.setTC(start_vert, tex_r.getTextureRect().getLeftTop(), tex_r.getTextureRect().getRightBot());
            xpos += g.getAdvanceX();
        }
        return *this;
    }

    inline TextRenderable& TextRenderable::setTextureUnit(uint32_t tid) {
        texture_unit_ = tid;
        return *this;
    }

    inline TextRenderable::Setter TextRenderable::getTextSetter() {
        return Setter(*this);
    }

    inline Vec2 TextRenderable::getBoundSize() {
        Geom& g = getGeom();

        uint32_t vertices_cnt = text_.size()*6;

        Vec2 left_top = g.getVertex<VertexDataPT::Vertex>(1).pos;
        Vec2 right_bot = g.getVertex<VertexDataPT::Vertex>(vertices_cnt-3).pos;
        return (right_bot - left_top)*local_transform_.getScale();
    }

    inline void TextRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        TextShader& ts = (TextShader&)s;

        ts.setUniformMat3(ts.u_transform, mvp);
        ts.setUniform1f(ts.u_z_coord, layer_z_);
        ts.setUniform1i(ts.u_texture, texture_unit_);
        ts.setUniform4fv(ts.u_color, color_, 1);
    }
}