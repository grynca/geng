#ifndef GENGSYSTEMTYPES_H
#define GENGSYSTEMTYPES_H

#include "types/Type.h"
#include "GameSystem.h"
#include "RenderSystem.h"
#include "MovementSystem.h"

namespace grynca {

    typedef TypesPack<
            RenderSystem,
            MovementSystem
            > GengSystemTypes;

}

#endif //GENGSYSTEMTYPES_H
