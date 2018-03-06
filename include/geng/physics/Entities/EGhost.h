#ifndef EGHOST_H
#define EGHOST_H

#include "geng/physics/Components/CCollider.h"
#include "../Components/CBody.h"
#include "../../core/Components/CTransform.h"
#include "../../core/Components/CSpeed.h"

namespace grynca {

    template <typename... AdditionalCompTypes>
    class EGhostT : public GengEntityDef<CTransformData, CSpeedData, CColliderData, CBodyData, AdditionalCompTypes...> {
        typedef GengEntityDef<CTransformData, CSpeedData, CColliderData, CBodyData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EGhostT);
    };

    class EGhost : public EGhostT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EGhost);
    };

    template <typename... AdditionalCompTypes>
    class EGhostTreeT : public EGhostT<CTreeTransformData> {
        typedef EGhostT<CTreeTransformData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EGhostTreeT);
    };

    class EGhostTree : public EGhostTreeT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EGhostTree);
    };
}

#endif //EGHOST_H
