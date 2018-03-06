#ifndef TEXTRENDERABLE_H
#define TEXTRENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class TextShader;
    class VertexDataPT;
    class GeomStateText;

    // Text position sets its left-bottom corner
    class TextRenderable : public Renderable {
    public:
        typedef TextShader ShaderType;
        typedef VertexDataPT VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhDynamic;

        struct DrawData : public Renderable::DrawData {
            Colorf color;
            u32 texture_id;
        };

        TextRenderable();
        ~TextRenderable();

        void setNewGeom(GeomUsageHint usage_hint = DefaultUsageHint);

        const GeomStateText& getTextState()const;
        Colorf getColor()const;

        Colorf& accColor();
        GeomStateText& accTextState();

        void setColor(const Colorf& clr);

        void onBeforeDraw(Shader& s);
    private:
        bool dirty_text_state_;
    };

}

#include "TextRenderable.inl"
#endif //TEXTRENDERABLE_H
