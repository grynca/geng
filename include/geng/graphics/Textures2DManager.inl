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

    inline u32 Textures2DManager::getTextureUnitsCount() {
        return u32(texture_units_.size());
    }

    inline Texture2D* Textures2DManager::accBoundTexture(u32 texture_unit_id) {
        ASSERT_M(texture_unit_id < texture_units_.size(), "Texture slot not available.");
        if (texture_units_[texture_unit_id] == Index::Invalid())
            return NULL;
        return &accItem(texture_units_[texture_unit_id]);
    }

    inline const Texture2D* Textures2DManager::accBoundTexture(u32 texture_unit_id)const {
        ASSERT_M(texture_unit_id < texture_units_.size(), "Texture slot not available.");
        if (texture_units_[texture_unit_id] == Index::Invalid())
            return NULL;
        return &getItem(texture_units_[texture_unit_id]);
    }
}