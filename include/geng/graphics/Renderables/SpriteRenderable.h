#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "../Renderable.h"
#include "../Shaders/SpriteShader.h"
#include "../VertexData/VertexDataPT.h"

namespace grynca {

    class SpriteRenderable : public Renderable {
    public:
        SpriteRenderable(Window& window, uint32_t layer_id, uint32_t texture_unit, const Vec2& size)
        : SpriteRenderable(window, layer_id, texture_unit, size, size/-2)      // default offset to center
        {}

        SpriteRenderable(Window& window, uint32_t layer_id, uint32_t texture_unit, const Vec2& size, const Vec2& offset)
         : Renderable(window), texture_unit_(texture_unit)
        {
            Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLE_FAN);
            geom_utils::addRect<VertexDataPT::Vertex>(geom);
            geom_utils::setRectSize<VertexDataPT::Vertex>(geom, 0, size);
            geom_utils::setRectOffset<VertexDataPT::Vertex>(geom, 0, offset);
            geom_utils::setRectTC<VertexDataPT::Vertex>(geom, 0, Vec2(0, 0), Vec2(1, 1));
            init<SpriteShader, VertexDataPT>(geom, layer_id);
        }

        virtual void preRender() override {
            SpriteShader& ss = (SpriteShader&)getShader();

            ss.setUniformMat3(ss.u_transform, mvp_);
            ss.setUniform1f(ss.u_z_coord, layer_z_);
            ss.setUniform1i(ss.u_texture, texture_unit_);
        }

        void setTextureUnit(int tid) { texture_unit_ = tid; }
    private:
        int texture_unit_;
    };

}

#endif //SPRITERENDERABLE_H
