#include "PgonTexturedRenderable.h"
#include "../Window.h"
#include "geng/graphics/Shaders/SimpleTexturedShader.h"
#include "../VertexData/VertexDataPT.h"

namespace grynca {

    inline PgonTexturedRenderable::PgonTexturedRenderable()
     : texture_unit_(InvalidId())
    {
    }

    template <typename GameType>
    inline PgonTexturedRenderable& PgonTexturedRenderable::init(GameType& game) {
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLE_FAN);
        RenderableBase::init<SimpleTexturedShader, VertexDataPT>(geom);
        return *this;
    }

    template <typename GameType>
    inline PgonTexturedRenderable& PgonTexturedRenderable::init(GameType& game, Geom& geom) {
        ASSERT(geom.getPrimitiveType() == GL_TRIANGLE_FAN);

        Window& window = game.template getModule<Window>();
        RenderableBase::init<SimpleTexturedShader, VertexDataPT>(geom);
        return *this;
    }

    inline PgonTexturedRenderable& PgonTexturedRenderable::setTextureUnit(uint32_t tid) {
        texture_unit_ = tid;
    }

    inline uint32_t PgonTexturedRenderable::getTextureUnit()const {
        return texture_unit_;
    }

    inline void PgonTexturedRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        SimpleTexturedShader& sts = (SimpleTexturedShader&)s;

        sts.setUniformMat3(sts.u_transform, mvp);
        sts.setUniform1f(sts.u_z_coord, layer_z_);
        sts.setUniform1i(sts.u_texture, texture_unit_);
    }
}