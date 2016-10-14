#ifndef GENGENTITYTYPES_H
#define GENGENTITYTYPES_H

#include "GengEntity.h"
#include "GengEntityFlags.h"
#include "CTransform.h"
#include "CMovable.h"
#include "CRenderables.h"
#include "CBody.h"
#include "CNetworked.h"

struct DummyEnt {

};

namespace grynca {

    typedef TypesPack<
        //TODO: add some entities
        DummyEnt
    > GengEntityTypes;

}

#endif //GENGENTITYTYPES_H
