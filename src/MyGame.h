#ifndef MYGAME_H
#define MYGAME_H

#include "incl.h"

class MyGame : public grynca::Game {
public:
    enum TextureIds {
        tidSprites = 0,
        tidArial = 1,
        tidCourier = 2      // monospace font
    };

    struct Assets {
        Index arial_pack_id;
        Index courier_pack_id;
        Index images_pack_id;
    } assets;


private:
    EntityIndex test_ent_id;
    EntityIndex shuttle_id;
    EntityIndex shuttle2_id;
    EntityIndex hud_id;
    EntityIndex dude_id;
    EntityIndex gui_root_id, gui_ch1_id, gui_ch2_id;

    virtual void init() override;
    virtual void update() override;
    virtual void tick() override;

    void initAssets();
};



#include "MyGame.inl"
#endif //MYGAME_H
