#ifndef GENGENTITYTYPES_H
#define GENGENTITYTYPES_H

#include "ENonMovable.h"
#include "EMovable.h"
#include "ERenderables.h"

struct DummyEnt {

};

namespace grynca {

    typedef TypesPack<
        //TODO: add some entities
        DummyEnt
    > GengEntityTypes;

}

#endif //GENGENTITYTYPES_H
