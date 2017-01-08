#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "maths/Transform.h"

namespace grynca {

    class CTransform {
    public:
        static RolesMask componentRoles() {
            return GERoles::erTransformMask();
        }

        const Transform& get();
        Transform& acc_();      // Warning: bypasses flags setting
        void set(const Transform& t, Entity& e);
        void setPosition(const Vec2& p, Entity& e);
        void setRotation(const Angle& r, Entity& e);
        void setScale(const Vec2& s, Entity& e);
        void move(const Vec2& m, Entity& e);
        void moveRelative(const Vec2& m, Entity& e);
        void rotate(const Angle& r, Entity& e);
        void scale(const Vec2& s, Entity& e);
    private:
        Transform transform_;
    };

}

#include "CTransform.inl"
#endif //CTRANSFORM_H
