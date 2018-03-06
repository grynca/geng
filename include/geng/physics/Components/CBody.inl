#include "CBody.h"
#include "CCollider.h"

namespace grynca {

    inline void CBodyCalcFromShape::init(const Material& material) {
        CBodyData* cbd = getData<CBodyData>();
        CColliderData* cco = getData<CColliderData>();

        ASSERT_M(cco->getShape().valid(), "Entity Shape must be set prior to calling this.");
        cbd->initWithShape(material, cco->getShape());
    }

}