#ifndef ETRIGGER_H
#define ETRIGGER_H

#include "geng/physics/Components/CCollider.h"
#include "../../core/Components/CTransform.h"

namespace grynca {

    template <typename... AdditionalCompTypes>
    class ETriggerT : public GengEntityDef<CTransformData, CColliderData, AdditionalCompTypes...> {
        typedef GengEntityDef<CTransformData, CColliderData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETriggerT);
    };

    class ETrigger : public ETriggerT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETrigger);
    };

    template <typename... AdditionalCompTypes>
    class ETriggerTreeT : public ETriggerT<CTreeTransformData> {
        typedef ETriggerT<CTreeTransformData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETriggerTreeT);
    };

    class ETriggerTree : public ETriggerTreeT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETriggerTree);
    };

    template <typename... AdditionalCompTypes>
    class ETriggerDynamicT : public ETriggerT<CSpeedData> {
        typedef ETriggerT<CSpeedData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETriggerDynamicT);
    };

    class ETriggerDynamic : public ETriggerDynamicT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(ETriggerDynamic);
    };
}

#endif //ETRIGGER_H
