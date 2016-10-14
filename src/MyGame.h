#ifndef MYGAME_H
#define MYGAME_H

#include "incl.h"

class MyGame : public grynca::Game<MyGame> {
public:
    enum TextureIds {
        tidSprites = 0,
        tidFonts = 1
    };

    struct Assets {
        Index fonts_pack_id;
        Index images_pack_id;
    } assets;


private:
    EntityIndex test_ent_id;
    EntityIndex shuttle_id;
    EntityIndex shuttle2_id;
    EntityIndex hud_id;

    virtual void init() override;
    virtual void update() override;
    virtual void tick() override;

    void initAssets();
};



#endif //MYGAME_H
