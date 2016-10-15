#ifndef GENGENTITYROLES_H
#define GENGENTITYROLES_H

#include "functions/meta.h"

namespace grynca {
    DEFINE_ENUM(GengEntityRoles,
            erRenderable,
            erCollidable,
            erTransform,
            erMovable,
            erNetworkedSv,
            erNetworkedCl
    );
}



#endif //GENGENTITYROLES_H
