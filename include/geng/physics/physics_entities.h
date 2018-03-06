#ifndef PHYSICS_ENTDEFS_H
#define PHYSICS_ENTDEFS_H

#include "Entities/ETrigger.h"
#include "Entities/EGhost.h"

namespace grynca {

    typedef grynca::TypesPack<
            ETrigger,
            ETriggerTree,
            ETriggerDynamic,
            EGhost,
            EGhostTree
    > PhysicsEntityTypes;

}

#endif //PHYSICS_ENTDEFS_H
