#ifndef GRAPHICS_ENTITIES_H
#define GRAPHICS_ENTITIES_H

#include "Entities/EVisual.h"
#include "Entities/EBody.h"
#include "Entities/DebugOverlay.h"

namespace grynca {

    typedef grynca::TypesPack<
            EVisual,
            EVisualDynamic,
            EVisualTree,
            EBody,
            EBodyTree
    > GraphicsEntityTypes;
}

#endif //GRAPHICS_ENTITIES_H
