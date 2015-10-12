#include "incl.h"
#include "HUD.h"


GameEntity& HUD::create(MyGame& game) {
// static
    GameEntity& ent = game.getSysEnt().getEntityManager().addItem();
    ent.setRoles({EntityRoles::erRenderable});
    HUD& me = ent.set<HUD>();
    TextRenderable& fps_label = me.getRenderables().addAs<TextRenderable, Renderable>().init(game, 10, 1, 0, 40, "FPS: ");
    fps_label.setCoordFrame(cfScreen);
    fps_label.getLocalTransform().setPosition({10, 10 + fps_label.getSize().getY()});

    TextRenderable& ups_label = me.getRenderables().addAs<TextRenderable, Renderable>().init(game, 10, 1, 0, 40, "UPS: ");
    ups_label.setCoordFrame(cfScreen);
    ups_label.getLocalTransform().setPosition({10, 20 + fps_label.getSize().getY() + ups_label.getSize().getY() });
    return ent;
}

void HUD::update(MyGame& game) {
    TextRenderable& fps_label = *(TextRenderable*)(getRenderables().get(0));
    fps_label.setText("FPS: "+std::to_string(game.getFPS()));

    TextRenderable& ups_label = *(TextRenderable*)(getRenderables().get(1));
    ups_label.setText("UPS: "+std::to_string(game.getUPS()));
}