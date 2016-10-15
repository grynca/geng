#include "PgonRenderable.h"
#include "../Window.h"
#include "geng/graphics/Shaders/SimpleColorShader.h"
#include "../VertexData/VertexDataP.h"
#include "assets/Image.h"

namespace grynca {

    inline PgonRenderable::PgonRenderable()
     : color_(Colorf::White())
    {
    }

    template <typename GameType>
    inline PgonRenderable& PgonRenderable::init(GameType& game) {
        Window& window = game.template getModule<Window>();
        Geom& geom = window.getVertices().get<VertexDataP>().addItem(GL_TRIANGLE_FAN);
        RenderableBase::init<SimpleColorShader, VertexDataP>(geom);
        return *this;
    }

    template <typename GameType>
    inline PgonRenderable& PgonRenderable::init(GameType& game, Geom& geom) {
        ASSERT(geom.getPrimitiveType() == GL_TRIANGLE_FAN);

        Window& window = game.template getModule<Window>();
        RenderableBase::init<SimpleColorShader, VertexDataP>(geom);
        return *this;
    }

    inline Colorf PgonRenderable::getColor()const {
        return color_;
    }

    inline PgonRenderable& PgonRenderable::setColor(const Colorf& clr) {
        color_ = clr;
    }

    inline void PgonRenderable::setUniforms(const Mat3& mvp, Shader& s) {
        SimpleColorShader& scs = (SimpleColorShader&)s;

        scs.setUniformMat3(scs.u_transform, mvp);
        scs.setUniform1f(scs.u_z_coord, layer_z_);
        scs.setUniform4fv(scs.u_color, color_.c_, 1);
    }
}