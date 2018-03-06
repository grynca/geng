#include <geng/GEFlags.h>
#include "CTransform.h"

namespace grynca {

    inline CTransformSetter::CTransformSetter()
     : dirty_flags_(0)
    {}

    inline CTransformSetter::~CTransformSetter() {
        updateFlags_();
    }

    inline void CTransformSetter::setTransform(const Transform &t) {
        dirty_flags_ |= fTransformedMask;
        CTransformData* data = getData<CTransformData>();
        data->set(t);
    }

    inline void CTransformSetter::setPosition(const Vec2& p) {
        dirty_flags_ |= fMovedMask;
        CTransformData* data = getData<CTransformData>();
        data->setPosition(p);
    }

    inline void CTransformSetter::setRotation(const Angle& r) {
        dirty_flags_ |= fRotatedMask;
        CTransformData* data = getData<CTransformData>();
        data->setRotation(r);
    }

    inline void CTransformSetter::setScale(const Vec2& s) {
        dirty_flags_ |= fScaledMask;
        CTransformData* data = getData<CTransformData>();
        data->setScale(s);
    }

    inline void CTransformSetter::move(const Vec2& m) {
        dirty_flags_ |= fMovedMask;
        CTransformData* data = getData<CTransformData>();
        data->move(m);
    }

    inline void CTransformSetter::moveRelative(const Vec2& m) {
        dirty_flags_ |= fMovedMask;
        CTransformData* data = getData<CTransformData>();
        data->moveRelative(m);
    }

    inline void CTransformSetter::rotate(const Angle& r) {
        dirty_flags_ |= fRotatedMask;
        CTransformData* data = getData<CTransformData>();
        data->rotate(r);
    }

    inline void CTransformSetter::scale(const Vec2& s) {
        dirty_flags_ |= fScaledMask;
        CTransformData* data = getData<CTransformData>();
        data->scale(s);
    }

    inline Transform& CTransformSetter::accTransform() {
        dirty_flags_ |= fTransformedMask;
        CTransformData* data = getData<CTransformData>();
        return *(Transform*)data;
    }

    inline void CTransformSetter::forceUpdateFlags() {
        updateFlags_();
        dirty_flags_ = 0;
    }

    inline void CTransformSetter::updateFlags_() {
        switch (dirty_flags_) {
            case 0:
                break;
            case fMovedMask:
                accEntity().setFlag(GEFlags::fEntityMovedId);
                break;
            case fRotatedMask:
                accEntity().setFlag(GEFlags::fEntityRotatedId);
                break;
            case fScaledMask:
                accEntity().setFlag(GEFlags::fEntityScaledId);
                break;

            default:
                // more than 1 flag set -> notify about general entity transform
                accEntity().setFlag(GEFlags::fEntityTransformedId);
                break;
        }
    }
}