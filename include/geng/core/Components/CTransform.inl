#include "CTransform.h"

namespace grynca {

    inline const Transform& CTransform::get() {
        return transform_;
    }

    // Warning: bypasses flags setting
    inline Transform& CTransform::acc_() {
        return transform_;
    }

    inline void CTransform::set(const Transform& t, Entity& e) {
        transform_ = t;
        e.setFlag(GEFlags::fMovedId);
        e.setFlag(GEFlags::fRotScaledId);
    }

    inline void CTransform::setPosition(const Vec2& p, Entity& e) {
        transform_.setPosition(p);
        e.setFlag(GEFlags::fMovedId);
    }

    inline void CTransform::setRotation(const Angle& r, Entity& e) {
        transform_.setRotation(r);
        e.setFlag(GEFlags::fRotScaledId);
    }

    inline void CTransform::setScale(const Vec2& s, Entity& e) {
        transform_.setScale(s);
        e.setFlag(GEFlags::fRotScaledId);
    }

    inline void CTransform::move(const Vec2& m, Entity& e) {
        if (m.isZero())
            return;
        transform_.move(m);
        e.setFlag(GEFlags::fMovedId);
    }

    inline void CTransform::moveRelative(const Vec2& m, Entity& e) {
        if (m.isZero())
            return;
        transform_.moveRelative(m);
        e.setFlag(GEFlags::fMovedId);
    }

    inline void CTransform::rotate(const Angle& r, Entity& e) {
        if (r == 0.0f)
            return;
        transform_.rotate(r);
        e.setFlag(GEFlags::fRotScaledId);
    }

    inline void CTransform::scale(const Vec2& s, Entity& e) {
        if (s.isZero())
            return;
        transform_.scale(s);
        e.setFlag(GEFlags::fRotScaledId);
    }
}