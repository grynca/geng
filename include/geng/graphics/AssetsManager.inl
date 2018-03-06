#include "AssetsManager.h"
#include "Window.h"

namespace grynca {

    inline AssetsManager::AssetsManager(Window& w)
     : window_(&w)
    {
    }

    inline Window& AssetsManager::getWindow() {
        return *window_;
    }

    inline Index AssetsManager::loadSpritesDirToTexture(const DirPath& dir_path, GLenum format, u32 texture_w, u32 texture_id) {
        ImagesPack& images = getImagesPacks().addItem();
        Textures2DManager& textures = window_->getTextures();

        images.loadDir(dir_path, format, texture_w);
        ustring p = dir_path.getPath();
        p.pop_back();
        Texture2D& sprites_tex = textures.addItem(Path(p).getFilename());
        images.setTextureId(texture_id);
        sprites_tex.bind(texture_id);
        sprites_tex.set(images.getPackImage());
        return images.getId();
    }

    inline Index AssetsManager::loadFontToTexture(const Path& font_path, const fast_vector<FontSize>& sizes, u32 texture_w, u32 texture_id,
                                                  const std::string& chars_to_load)
    {
        FontPack& fonts = getFontsPacks().addItem();
        Textures2DManager& textures = window_->getTextures();
        if (!chars_to_load.empty())
            fonts.setCharsToLoad(chars_to_load);
        fonts.loadFont(font_path, sizes, texture_w);
        if (fonts.isNull())
            return Index::Invalid();
        Texture2D& fonts_tex = textures.addItem(font_path.getFilenameWOExtension());
        fonts.setTextureId(texture_id);
        fonts_tex.bind(texture_id);
        fonts_tex.set(fonts.getPackImage());

        return fonts.getId();
    }

    inline Index AssetsManager::loadSpritesDirToTextureThrow(const DirPath& dir_path, GLenum format, u32 texture_w, u32 texture_id) {
        Index id = loadSpritesDirToTexture(dir_path, format, texture_w, texture_id);
        if (!id.isValid()) {
            throw Exception(ustring("Error loading sprites: '") + dir_path.getFilename() + "'.");
        }
        return id;
    }

    inline Index AssetsManager::loadFontToTextureThrow(const Path& font_path, const fast_vector<FontSize>& sizes, u32 texture_w, u32 texture_id,
                                 const std::string& chars_to_load)
    {
        Index id = loadFontToTexture(font_path, sizes, texture_w, texture_id, chars_to_load);
        if (!id.isValid()) {
            throw Exception(ustring("Error loading sprites: '") + font_path.getFilename() + "'.");
        }
        return id;
    }

}