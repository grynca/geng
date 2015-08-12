#include "Textures2DManager.h"
#include "glinclude.h"

namespace grynca {
    Textures2DManager::Textures2DManager() {
        int max_texture_units;
        GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units));
        texture_units_.resize(size_t(max_texture_units), uint32_t(-1));
    }

    uint32_t Textures2DManager::getTextureUnitsCount() {
        return uint32_t(texture_units_.size());
    }

    Texture2D* Textures2DManager::getBoundTexture(uint32_t slot_id) {
        ASSERT(slot_id < texture_units_.size(), "Texture slot not available.");
        if (texture_units_[slot_id] == uint32_t(-1))
            return NULL;
        return &getItem(texture_units_[slot_id]);
    }
}