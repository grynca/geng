#include "../incl.h"
#include "HUD.h"


Entity HUD::create(MyGame& game) {
// static
    Entity ent = game.createEntity(GET_ETYPE_ID(HUD));
    CRenderables& rs = ent.getComponent<CRenderables>();
    TextRenderable& fps_label = rs.addRenderable<TextRenderable>().init(game);
    fps_label.setTextureUnit(1);
    fps_label.setLayerId(10);
    fps_label.getTextSetter().setFont(game.assets.fonts_pack_id).setFontSize(40).setText("FPS: ");
    fps_label.setCoordFrame(cfScreen);
    fps_label.accLocalTransform().setPosition({10, 40});

    TextRenderable& ups_label = rs.addRenderable<TextRenderable>().init(game);
    ups_label.setTextureUnit(1);
    ups_label.setLayerId(10);
    ups_label.getTextSetter().setFont(game.assets.fonts_pack_id).setFontSize(40).setText("UPS: ");
    ups_label.setCoordFrame(cfScreen);
    ups_label.accLocalTransform().setPosition({10, 90});
    return ent;
}

void HUD::update(Entity& e, MyGame& game) {
//static
    Renderables& rs = e.getComponent<CRenderables>().accRenderables();
    TextRenderable& fps_label = rs[0].get<TextRenderable>();
    fps_label.getTextSetter().setText("FPS: "+std::to_string(game.getFPS()));

    TextRenderable& ups_label = rs[1].get<TextRenderable>();
    ups_label.getTextSetter().setText("UPS: "+std::to_string(game.getUPS()));
}