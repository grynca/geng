#ifndef ETRANSFORM_H
#define ETRANSFORM_H

#include "maths/Transform.h"
#include "GengEntityRoles.h"

namespace grynca {

    class ETransform : public virtual GengEntity {
    public:

        ETransform() {
            addRoles({GengEntityRoles::erTransform});
        }

        const Transform& getTransform() {
            return transform_;
        }

        void setPosition(const Vec2& p) {
            transform_.setPosition(p);
            getFlags().set(GengEntity::fMoved);
        }

        void setRotation(const Angle& r) {
            transform_.setRotation(r);
            getFlags().set(GengEntity::fRotated);
        }

        void setScale(const Vec2& s) {
            transform_.setScale(s);
            getFlags().set(GengEntity::fScaled);
        }

        void move(const Vec2& m) {
            if (m.isZero())
                return;
            transform_.move(m);
            getFlags().set(GengEntity::fMoved);
        }

        void moveRelative(const Vec2& m) {
            if (m.isZero())
                return;
            transform_.moveRelative(m);
            getFlags().set(GengEntity::fMoved);
        }

        void rotate(const Angle& r) {
            if (r == 0.0f)
                return;
            transform_.rotate(r);
            getFlags().set(GengEntity::fRotated);
        }

        void scale(const Vec2& s) {
            if (s.isZero())
                return;
            transform_.scale(s);
            getFlags().set(GengEntity::fScaled);
        }
    private:
        Transform transform_;
    };

}

#endif //ETRANSFORM_H
