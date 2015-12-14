#ifndef TEXTRENDERABLE_H
#define TEXTRENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    // fw
    class Window;
    class AssetsManager;

    class TextRenderable : public Renderable {
    public:
        class Setter {
        public:
            ~Setter();
            Setter& setFont(uint32_t font_pack_id);
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
        TextRenderable& init(GameType& game, Geom& geom);       // shared geom

        AssetsManager& getAssets()const;
        const std::string& getText()const;
        uint32_t getFontSize()const;
        uint32_t getFontPackId()const;
        void getColor(float* c)const;
        uint32_t getTextureUnit()const;

        TextRenderable& setColor(float r, float g, float b, float a = 1.0f);
        TextRenderable& setTextureUnit(uint32_t tid);
        Setter getTextSetter();     // changes geom data

        virtual void preRender() override;
    private:
        friend class Setter;
        TextRenderable& updateTextGeom_();

        AssetsManager* assets_;
        uint32_t texture_unit_;
        uint32_t font_pack_id_;
        uint32_t font_size_;
        std::string text_;
        float color_[4];
    };

}

#include "TextRenderable.inl"
#endif //TEXTRENDERABLE_H
