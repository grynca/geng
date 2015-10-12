#ifndef TEXTURES2DMANAGER_H
#define TEXTURES2DMANAGER_H

#include "types/Manager.h"
#include "Texture2D.h"

namespace grynca {

    class Textures2DManager : public Manager<Texture2D> {
    public:
        Textures2DManager();

        uint32_t getTextureUnitsCount();
        Texture2D* getBoundTexture(uint32_t texture_unit_id);
    private:
        friend class Texture2D;

        fast_vector<uint32_t> texture_units_;
    };

}

#endif //TEXTURES2DMANAGER_H
