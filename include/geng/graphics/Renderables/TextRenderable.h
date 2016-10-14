#ifndef TEXTRENDERABLE_H
#define TEXTRENDERABLE_H

#include "RenderableBase.h"

namespace grynca {

    // fw
    class Window;
    class AssetsManager;

    // Text position sets its left-bottom corner
    class TextRenderable : public RenderableBase {
    public:
        class Setter {
        public:
            ~Setter();
            Setter& setFont(Index font_pack_id);
            Setter& setFontSize(uint32_t font_size);
            Setter& setText(const std::string& t);

        private:
            friend class TextRenderable;
            Setter(TextRenderable& tr);

            TextRenderable* tr_;
        };

    public:
        TextRenderable();

        template <typename GameType>
        TextRenderable& init(GameType& game);
        template <typename GameType>
        TextRenderable& init(GameType& game, Geom& geom);       // reuses existing geom

        AssetsManager& getAssets()const;
        const std::string& getText()const;
        uint32_t getFontSize()const;
        Index getFontPackId()const;
        void getColor(float* c)const;
        uint32_t getTextureUnit()const;

        TextRenderable& setColor(float r, float g, float b, float a = 1.0f);
        TextRenderable& setTextureUnit(uint32_t tid);
        Setter getTextSetter();     // changes geom data
        Vec2 getBoundSize();

        virtual void setUniforms(const Mat3& mvp, Shader& s) override;
    private:
        friend class Setter;
        TextRenderable& updateTextGeom_();

        AssetsManager* assets_;
        uint32_t texture_unit_;
        Index font_pack_id_;
        uint32_t font_size_;
        std::string text_;
        float color_[4];
    };

}

#include "TextRenderable.inl"
#endif //TEXTRENDERABLE_H
