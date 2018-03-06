#ifndef GENGENTITYROLES_H
#define GENGENTITYROLES_H

#include "types/Mask.h"
#include "functions/enum.h"

namespace grynca {
    DEFINE_ENUM(GERoles,
            erGui,
            erTransform,
            erSpeed,
            erCollider,
            erBody,

            erRenderable,
            erTreeTransform,
            erTreeJoint,
            erNetworkedSv,
            erNetworkedCl
    );
}



#endif //GENGENTITYROLES_H
