#include "GeomStateBase.h"
#include "../Geom.h"

namespace grynca {

    inline GeomStateBase::GeomStateBase(GeomStateType type_id, VertexData& vd, Index geom_id)
     : bits_pack_(0), vd_(&vd), geom_id_(geom_id)
    {
        bits_pack_ = SET_BITS(bits_pack_, 0, 31, u32(type_id));
        makeDirty();
    }

    GeomStateType GeomStateBase::getTypeId()const {
        return GeomStateType(GET_BITS(bits_pack_, 0, 31));
    }

    u32 GeomStateBase::getId()const {
        return vd_->getGeomStates().getStateId_(getTypeId(), this);
    }

    inline const Geom& GeomStateBase::getGeom()const {
        ASSERT(vd_);
        return vd_->getItem(geom_id_);
    }

    inline Geom& GeomStateBase::accGeom() {
        ASSERT(vd_);
        return vd_->accItem(geom_id_);
    }

    inline void GeomStateBase::setGeom(const Geom& geom) {
        vd_ = &geom.getManager();
        geom_id_ = geom.getId();
    }

    inline bool GeomStateBase::isDirty()const {
        return GET_BIT(bits_pack_, 31);
    }

    inline void GeomStateBase::makeDirty() {
        if (!isDirty()) {
            vd_->accGeomStates().dirty_[getTypeId()].push_back(getId());
            bits_pack_ = SET_BIT(bits_pack_, 31);
        }
    }

    inline void GeomStateBase::clearDirty() {
        bits_pack_ = CLEAR_BIT(bits_pack_, 31);
    }

}