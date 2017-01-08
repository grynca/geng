#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "../../Game.h"
#include "../Renderables/RectRenderable.h"

namespace grynca {

    class GUIElement : public GengEntityDef<CTransform, CDeltaTransform, CRenderables> {
    public:
        static void addChild(Entity& me, Entity& child, const Vec2& pos) {
            me.getComponentSetter<CDeltaTransform>()
                    .addChild(child);

            child.getComponentSetter<CDeltaTransform>()
                    .setPosition(pos);
        }

        static void setBackgroundRect(Entity& me, const Vec2& size, u16 layer_id, const Colorf& color, const Vec2& offset = NormOffset::LeftTop() ) {
            CRenderables& rs = me.getComponent<CRenderables>();
            auto r = rs.addRenderable<RectRenderable>(GeomState::uhStatic);
            r.setSize(size)
                .setGeomNormOffset(offset)
                .setColor(color);
        }
    };
}

#endif //GUIELEMENT_H
