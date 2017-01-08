#ifndef TEXTRENDERABLE_H
#define TEXTRENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class TextShader;
    class VertexDataPT;
    class TextState;

    // Text position sets its left-bottom corner
    class TextRenderable : public Renderable {
    public:
        typedef TextShader ShaderType;
        typedef VertexDataPT VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhDynamic);

        TextRenderable(const Renderer2D::ItemRef& rt) : Renderable(rt) {}

        const TextState& getTextState()const;
        Colorf getColor()const;
        u32 getTextureUnit()const;

        Colorf& accColor();
        TextState& accTextState();

        TextRenderable& setColor(const Colorf& clr);
        TextRenderable& setTextureUnit(u32 tid);
        TextRenderable& setPosition(const Vec2& pos);

        Vec2 calcBoundSize();
    };

}

#include "TextRenderable.inl"
#endif //TEXTRENDERABLE_H
