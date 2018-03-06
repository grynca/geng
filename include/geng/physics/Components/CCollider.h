#ifndef CCOLLIDER_H
#define CCOLLIDER_H

#include "../../GERoles.h"
#include "../../core/GengEntity.h"
#include "maths/shapes/ARect.h"

namespace grynca {

    class CColliderData : public Collider {
    public:
        static RolesMask componentRoles() {
            return GERoles::erColliderMask();
        }
    };

    class CColliderSetter : public EntityAccessor<CColliderData> {
        typedef EntityAccessor<CColliderData> Base;
    public:
        MOVE_ONLY(CColliderSetter);

        CColliderSetter();
        ~CColliderSetter();

        Shape& accShape();

        ARect& accBound();
        void setBound(const ARect& b);

        // tighter bound (is not rotation invariant)
        //  e.g. for: static bodies, circle, squere ...
        void calcTightBound();

        // calculate larger rotation invariant bound
        //      e.g. needed for rectangle ...
        void calcRotationInvariantBound();
    private:
        bool dirty_;
    };
}

#include "CCollider.inl"
#endif //CCOLLIDER_H
