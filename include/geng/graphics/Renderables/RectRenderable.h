#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "../Shaders/RectShader.h"
#include "../VertexData/VertexDataP.h"
#include "../geom_utils.h"

namespace grynca {

    class RectRenderable : public Renderable {
    public:
        RectRenderable(Window& window, uint32_t layer_id, const Vec2& size)
         : RectRenderable(window, layer_id, size, size/-2)      // default offset to center
        {}

        RectRenderable(Window& window, uint32_t layer_id, const Vec2& size, const Vec2& offset)
         : Renderable(window)
        {
            color_[0] = color_[1] = color_[2] = color_[3] = 1.0f;
            Geom& geom = window.getVertices().get<VertexDataP>().addItem(GL_TRIANGLE_FAN);
            geom_utils::addRect<VertexDataP::Vertex>(geom);
            geom_utils::setRectSize<VertexDataP::Vertex>(geom, 0, size);
            geom_utils::setRectOffset<VertexDataP::Vertex>(geom, 0, offset);
            init<RectShader, VertexDataP>(geom, layer_id);
        }

        virtual void preRender() override {
            RectShader& rs = (RectShader&)getShader();

            rs.setUniformMat3(rs.u_transform, mvp_);
            rs.setUniform1f(rs.u_z_coord, layer_z_);
            rs.setUniform4fv(rs.u_color, color_, 1);
        }

        void setColor(float r, float g, float b, float a = 1.0f) {
            color_[0] = r;
            color_[1] = g;
            color_[2] = b;
            color_[3] = a;
        }

        Vec2 getSize() {
            return geom_utils::getRectSize<VertexDataP::Vertex>(getGeom(), 0);
        }
        Vec2 getOffset() {
            return geom_utils::getRectOffset<VertexDataP::Vertex>(getGeom(), 0);
        }
        void setSize(const Vec2& size) {
            geom_utils::setRectSize<VertexDataP::Vertex>(getGeom(), 0, size);
        }

        void setOffset(const Vec2& offset) {
            geom_utils::setRectOffset<VertexDataP::Vertex>(getGeom(), 0, offset);
        }
    private:
        float color_[4];
    };
}

#endif //RECTRENDERABLE_H
