#include "incl.h"
#include "HUD.h"


GameEntity& HUD::create(MyGame& game) {
// static
    GameEntity& ent = game.getSysEnt().getEntityManager().addItem();
    HUD& me = ent.set<HUD>();
    TextRenderable& fps_label = me.getRenderables().addAs<TextRenderable, Renderable>().init(game);
    fps_label.setTextureUnit(1);
    fps_label.setLayerId(10);
    fps_label.getTextSetter().setFont(0).setFontSize(40).setText("FPS: ");
    fps_label.setCoordFrame(cfScreen);
    fps_label.getLocalTransform().setPosition({10, 40});

    TextRenderable& ups_label = me.getRenderables().addAs<TextRenderable, Renderable>().init(game);
    ups_label.setTextureUnit(1);
    ups_label.setLayerId(10);
    ups_label.getTextSetter().setFont(0).setFontSize(40).setText("UPS: ");
    ups_label.setCoordFrame(cfScreen);
    ups_label.getLocalTransform().setPosition({10, 90});
    return ent;
}

void HUD::update(MyGame& game) {
    TextRenderable& fps_label = *(TextRenderable*)(getRenderables().get(0));
    fps_label.getTextSetter().setText("FPS: "+std::to_string(game.getFPS()));

    TextRenderable& ups_label = *(TextRenderable*)(getRenderables().get(1));
    ups_label.getTextSetter().setText("UPS: "+std::to_string(game.getUPS()));
}