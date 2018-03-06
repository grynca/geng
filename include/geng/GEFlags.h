#ifndef GENG_ENTITY_FLAGS_H
#define GENG_ENTITY_FLAGS_H

#include "types/Mask.h"
#include "functions/enum.h"

namespace grynca {

    DEFINE_ENUM(GEFlags,
                  fEntityMoved,
                  fEntityRotated,
                  fEntityScaled,
                  fEntityTransformed,
                  fCompositeTransformed,
                  fCompositeColliderChanged,
                  fCompositeChanged,     // enabled/disabled parts
                  fBoundChanged
    );
}

#endif //GENG_ENTITY_FLAGS_H
