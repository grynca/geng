#include "types/Type.h"
#include "physics_includes.h"

#define SET_TYPE_ID(Type, Id) TypeInfoManager<PhysicsDomain>::setTypeId<Type>(Id);

namespace grynca {
    void PhysicsDomain::setIds() {
        //static
        SET_TYPE_ID(Speed, 0);
    }
}

#undef SET_TYPE_ID