#ifndef MYASSETS_H
#define MYASSETS_H

#include "incl.h"
#include "assets.h"

class MyAssets {
public:
    enum TextureIds {
        tidSprites = 0,
        tidFonts = 1
    };

    static void init(MyGame& g) {
        AssetsManager& am = g.getModule<AssetsManager>();
        ImagesPack& images = am.getImagesPacks().addItem();
        FontPack& fonts = am.getFontsPacks().addItem();
        Textures2DManager& textures = g.getModule<Window>().getTextures();

        images.loadDir("data/sprites", GL_RGBA, 2048);
        Texture2D& sprites_tex = textures.addItem("sprites");
        sprites_tex.bind(tidSprites);
        sprites_tex.set(images.getPackImage());

        fonts.loadFont("data/fonts/arial.ttf", {{10, 50}}, 2048);
        Texture2D& fonts_tex = textures.addItem("fonts");
        fonts_tex.bind(tidFonts);
        fonts_tex.set(fonts.getPackImage());
    }
};

#endif //MYASSETS_H
