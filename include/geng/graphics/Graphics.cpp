#include "types/Type.h"
#include "graphics_includes.h"

#define SET_TYPE_ID(Type, Id) TypeInfoManager<Graphics>::setTypeId<Type>(Id);

namespace grynca {
    void Graphics::setIds() {
    //static
        SET_TYPE_ID(Window, 0);
        SET_TYPE_ID(Events, 1);
        SET_TYPE_ID(ViewPort, 2);
        SET_TYPE_ID(Textures2DManager, 3);
        SET_TYPE_ID(Texture2D, 4);
        SET_TYPE_ID(Shaders, 5);
        SET_TYPE_ID(Shader, 6);
        SET_TYPE_ID(Vertices, 7);
        SET_TYPE_ID(VertexData, 8);
        SET_TYPE_ID(VertexAttribInfo, 9);
        SET_TYPE_ID(Renderer2D, 10);
        SET_TYPE_ID(Geom, 11);
        SET_TYPE_ID(DrawSortingKey, 12);
        SET_TYPE_ID(VertexDataP, 13);
        SET_TYPE_ID(VertexDataPT, 14);
        SET_TYPE_ID(CircleShader, 15);
        SET_TYPE_ID(CircleRenderable, 16);
        SET_TYPE_ID(RectShader, 17);
        SET_TYPE_ID(RectRenderable, 18);
        SET_TYPE_ID(SpriteShader, 19);
        SET_TYPE_ID(SpriteRenderable, 20);
    }
}

#undef SET_TYPE_ID