#ifndef CBODY_H
#define CBODY_H

#include "../../GERoles.h"
#include "../../core/GengEntity.h"

namespace grynca {

    // fw
    class CColliderData;

    class CBodyData : public Body {
    public:
        static RolesMask componentRoles() {
            return GERoles::erBodyMask();
        }
    };

    class CBodyCalcFromShape : public EntityAccessor<CBodyData, CColliderData> {
        typedef EntityAccessor<CBodyData, CColliderData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(CBodyCalcFromShape);

        void init(const Material& material);
    };
}
#include "CBody.inl"
#endif //CBODY_H
