#ifndef TEXTURES2DMANAGER_H
#define TEXTURES2DMANAGER_H

#include "types/Manager.h"

namespace grynca {

    class Texture2D;

    class Textures2DManager : public Manager<Texture2D> {
    public:
        Textures2DManager();

        uint32_t getTextureUnitsCount();
        Texture2D* getBoundTexture(uint32_t texture_unit_id);
    private:
        friend class Texture2D;

        fast_vector<Index> texture_units_;
    };
}

#include "Textures2DManager.inl"
#endif //TEXTURES2DMANAGER_H
