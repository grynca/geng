#ifndef TEXTURES2DMANAGER_H
#define TEXTURES2DMANAGER_H

#include "types/Manager.h"

namespace grynca {

    class Texture2D;

    class Textures2DManager : public Manager<Texture2D> {
    public:
        Textures2DManager();

        u32 getTextureUnitsCount();
        Texture2D* accBoundTexture(u32 texture_unit_id);
        const Texture2D* accBoundTexture(u32 texture_unit_id)const;
    private:
        friend class Texture2D;

        fast_vector<Index> texture_units_;
    };
}

#include "Textures2DManager.inl"
#endif //TEXTURES2DMANAGER_H
