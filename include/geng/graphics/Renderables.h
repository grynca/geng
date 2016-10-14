#ifndef RENDERABLES_H
#define RENDERABLES_H

#include "types/Variant.h"

#include "Renderables/CircleRenderable.h"
#include "Renderables/RectRenderable.h"
#include "Renderables/RectBorderRenderable.h"
#include "Renderables/SpriteRenderable.h"
#include "Renderables/TextRenderable.h"

namespace grynca {

    typedef TypesPack<
            CircleRenderable,
            RectRenderable,
            RectBorderRenderable,
            SpriteRenderable,
            TextRenderable
    > RenderablesTP;

    typedef Variant<RenderablesTP> Renderable;

    typedef fast_vector<Renderable> Renderables;

    static inline void printRenderableSize() {
#ifdef DEBUG_BUILD
        std::cout << "RenderableBase size: " << sizeof(Renderable) << " bytes" << std::endl;
#endif
    }
}

#endif //RENDERABLES_H
