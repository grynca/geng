#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "../GengEntity.h"
#include "maths/Transform.h"

namespace grynca {

    class CTransformData : public Transform {
    public:
        static RolesMask componentRoles() {
            return GERoles::erTransformMask();
        }
    };

    class CTransformSetter : public EntityAccessor<CTransformData> {
        typedef EntityAccessor<CTransformData> Base;
    public:
        MOVE_ONLY(CTransformSetter);

        CTransformSetter();
        ~CTransformSetter();

        void setTransform(const Transform &t);
        void setPosition(const Vec2& p);
        void setRotation(const Angle& r);
        void setScale(const Vec2& s);
        void move(const Vec2& m);
        void moveRelative(const Vec2& m);
        void rotate(const Angle& r);
        void scale(const Vec2& s);

        Transform& accTransform();

        // is done automatically in destructor
        void forceUpdateFlags();
    private:
        enum {
            fMovedMask = BIT_MASK(0),
            fRotatedMask = BIT_MASK(1),
            fScaledMask = BIT_MASK(2),
            fTransformedMask = fMovedMask | fRotatedMask | fScaledMask
        };

        void updateFlags_();

        u8 dirty_flags_;
    };

}

#include "CTransform.inl"
#endif //CTRANSFORM_H