#include "CCollider.h"
#include "../../core/Components/CTransform.h"
#include "maths/shapes/ARect.h"

namespace grynca {
    
    inline CColliderSetter::CColliderSetter()
     : dirty_(false)
    {}
    
    inline CColliderSetter::~CColliderSetter() {
        if (dirty_) {
            this->accEntity().setFlag(GEFlags::fBoundChangedId);
        }
    }

    inline Shape& CColliderSetter::accShape() {
        return getData<CColliderData>()->accShape();
    }

    inline ARect& CColliderSetter::accBound() {
        dirty_ = true;
        return getData<CColliderData>()->accBoundARect();
    }
    
    inline void CColliderSetter::setBound(const ARect& b) {
        dirty_ = true;
        getData<CColliderData>()->setBoundRect(b);
    }

    inline void CColliderSetter::calcTightBound() {
        CColliderData* data = getData<CColliderData>();
        ASSERT_M(data->getShape().valid(), "Entity Shape must be set prior to calling this.");
        setBound(data->getShape().calcARectBound());
    }

    inline void CColliderSetter::calcRotationInvariantBound() {
        CColliderData* data = getData<CColliderData>();
        ASSERT_M(data->getShape().valid(), "Entity Shape must be set prior to calling this.");
        setBound(data->getShape().calcARectBound().calcRotInvBound());
    }

}