#include "types/Type.h"
#include "physics_includes.h"

#define SET_TYPE_ID(Type, Id) TypeInfoManager<Physics>::setTypeId<Type>(Id);

namespace grynca {
    void Physics::setIds() {
        //static
        SET_TYPE_ID(Speed, 0);
    }
}

#undef SET_TYPE_ID