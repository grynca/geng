#ifndef GENGENTITYTYPES_H
#define GENGENTITYTYPES_H

#include "GengEntity.h"
#include "ETransform.h"
#include "EMovable.h"
#include "ERenderables.h"
#include "ECollidables.h"

struct DummyEnt {

};

namespace grynca {

    typedef TypesPack<
        //TODO: add some entities
        DummyEnt
    > GengEntityTypes;

}

#endif //GENGENTITYTYPES_H
