#ifndef GENG_ENTITY_FLAGS_H
#define GENG_ENTITY_FLAGS_H

#include "GengEntityRoles.h"
#include <bitset>

namespace grynca {

    DEFINE_ENUM(GengEntityFlags,
                  fMoved,
                  fRotated,
                  fScaled
    );
}

#endif //GENG_ENTITY_FLAGS_H
