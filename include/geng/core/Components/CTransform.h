#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "maths/Transform.h"
#include "../GengEntityRoles.h"

namespace grynca {

    class CTransform {
    public:
        static RolesMask componentRoles() {
            return {GengEntityRoles::erTransform};
        }

        Transform& get() {
            return transform_;
        }

    // setters, also sets flags to entity
        void setPosition(const Vec2& p, Entity& e) {
            transform_.setPosition(p);
            e.setFlag(GengEntityFlags::fMoved);
        }

        void setRotation(const Angle& r, Entity& e) {
            transform_.setRotation(r);
            e.setFlag(GengEntityFlags::fRotated);
        }

        void setScale(const Vec2& s, Entity& e) {
            transform_.setScale(s);
            e.setFlag(GengEntityFlags::fScaled);
        }

        void move(const Vec2& m, Entity& e) {
            if (m.isZero())
                return;
            transform_.move(m);
            e.setFlag(GengEntityFlags::fMoved);
        }

        void moveRelative(const Vec2& m, Entity& e) {
            if (m.isZero())
                return;
            transform_.moveRelative(m);
            e.setFlag(GengEntityFlags::fMoved);
        }

        void rotate(const Angle& r, Entity& e) {
            if (r == 0.0f)
                return;
            transform_.rotate(r);
            e.setFlag(GengEntityFlags::fRotated);
        }

        void scale(const Vec2& s, Entity& e) {
            if (s.isZero())
                return;
            transform_.scale(s);
            e.setFlag(GengEntityFlags::fScaled);
        }

        // matrix is updated each update frame in TransformSystem
        //  if you want more current matrix compute it via transform_.calcMatrix()
        Mat3& accMatrix() {
            return matrix_;
        }
    private:
        Transform transform_;
        Mat3 matrix_;
    };

}

#endif //CTRANSFORM_H
