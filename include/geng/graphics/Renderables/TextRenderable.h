#ifndef TEXTRENDERABLE_H
#define TEXTRENDERABLE_H

#include "../Renderable.h"

namespace grynca {

    // fw
    class Window;
    class AssetsManager;

    class TextRenderable : public Renderable {
    public:
        TextRenderable();

        template <typename GameType>
        TextRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t font_pack_id, uint32_t font_size, const std::string& text);

        AssetsManager& getAssets();

        virtual void preRender() override;

        void setFont(uint32_t font_pack_id);
        void setFont(uint32_t font_pack_id, uint32_t font_size);
        void setFontSize(uint32_t font_size);
        void setText(const std::string& t);
        const std::string& getText()const;
        const uint32_t getFontSize()const;
        const uint32_t getFontPackId()const;


        void setColor(float r, float g, float b, float a = 1.0f);
        Vec2 getSize();
    private:
        void updateTextGeom_();

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
