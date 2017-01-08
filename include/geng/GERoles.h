#ifndef GENGENTITYROLES_H
#define GENGENTITYROLES_H

#include "functions/meta.h"

namespace grynca {
    DEFINE_ENUM(GERoles,
            erGui,
            erRenderable,
            erCollidable,
            erTransform,
            erTreeTransform,
            erMovable,
            erNetworkedSv,
            erNetworkedCl
    );
}



#endif //GENGENTITYROLES_H
