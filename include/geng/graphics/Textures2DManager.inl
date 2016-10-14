#include "Textures2DManager.h"
#include "glinclude.h"
#include "Texture2D.h"
#include "types/Index.h"

namespace grynca {
    inline Textures2DManager::Textures2DManager() {
        int max_texture_units;
        GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units));
        texture_units_.resize(size_t(max_texture_units), Index::Invalid());
    }

    inline uint32_t Textures2DManager::getTextureUnitsCount() {
        return uint32_t(texture_units_.size());
    }

    inline Texture2D* Textures2DManager::getBoundTexture(uint32_t texture_unit_id) {
        ASSERT_M(texture_unit_id < texture_units_.size(), "Texture slot not available.");
        if (texture_units_[texture_unit_id] == Index::Invalid())
            return NULL;
        return &getItem(texture_units_[texture_unit_id]);
    }
}