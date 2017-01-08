#ifndef GENG_ENTITY_FLAGS_H
#define GENG_ENTITY_FLAGS_H

#include "functions/meta.h"

namespace grynca {

    DEFINE_ENUM(GEFlags,
                  fMoved,
                  fRotScaled,
                  fRenderablesChanged
    );
}

#endif //GENG_ENTITY_FLAGS_H
