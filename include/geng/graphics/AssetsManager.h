#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "assets/AssetsManagerBase.h"

namespace grynca {

    // fw
    class Window;

    class AssetsManager : public AssetsManagerBase {
    public:
        AssetsManager(Window& w);

        Window& getWindow();

        // returns pack id on success, Index::Invalid() on failure
        Index loadSpritesDirToTexture(const DirPath& dir_path, GLenum format, u32 texture_w, u32 texture_id);
        Index loadFontToTexture(const Path& font_path, const fast_vector<FontSize>& sizes, u32 texture_w, u32 texture_id,
                                const std::string& chars_to_load = std::string());  // when empty default chars are loaded

        // returns pack id on success, throws Exception() on failure
        Index loadSpritesDirToTextureThrow(const DirPath& dir_path, GLenum format, u32 texture_w, u32 texture_id);
        Index loadFontToTextureThrow(const Path& font_path, const fast_vector<FontSize>& sizes, u32 texture_w, u32 texture_id,
                                const std::string& chars_to_load = std::string());  // when empty default chars are loaded

    private:
        Window* window_;
    };

}

#include "AssetsManager.inl"
#endif //ASSETSMANAGER_H
