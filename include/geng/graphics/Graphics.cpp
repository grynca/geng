#include "types/Type.h"
#include "graphics_includes.h"

#define SET_TYPE_ID(Type, Id) TypeInfoManager<Graphics>::setTypeId<Type>(Id);

namespace grynca {
    void Graphics::setIds() {
    //static
        SET_TYPE_ID(Window, 0);
        SET_TYPE_ID(ViewPort, 1);
        SET_TYPE_ID(Textures2DManager, 2);
        SET_TYPE_ID(Texture2D, 3);
        SET_TYPE_ID(Shaders, 4);
        SET_TYPE_ID(Shader, 5);
        SET_TYPE_ID(Vertices, 6);
        SET_TYPE_ID(VertexData, 7);
        SET_TYPE_ID(VertexAttribInfo, 8);
        SET_TYPE_ID(Renderer2D, 9);
        SET_TYPE_ID(Geom, 10);
        SET_TYPE_ID(DrawSortingKey, 11);
        SET_TYPE_ID(VertexDataP, 12);
        SET_TYPE_ID(VertexDataPT, 13);
        SET_TYPE_ID(CircleShader, 14);
        SET_TYPE_ID(CircleRenderable, 15);
        SET_TYPE_ID(RectShader, 16);
        SET_TYPE_ID(RectRenderable, 17);
        SET_TYPE_ID(SpriteShader, 18);
        SET_TYPE_ID(SpriteRenderable, 19);
    }
}

#undef SET_TYPE_ID