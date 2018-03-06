#ifndef GEOMSTATEBASE_H
#define GEOMSTATEBASE_H

#include "../geom_enums.h"

namespace grynca {

    // fw
    class GeomState;
    class VertexData;
    class Geom;

    class GeomStateBase {
    public:
        GeomStateBase(GeomStateType type_id, VertexData& vd, Index geom_id);

        GeomStateType getTypeId()const;
        u32 getId()const;

        const Geom& getGeom()const;
        Geom& accGeom();
        void setGeom(const Geom& geom);

        bool isDirty()const;
        void makeDirty();
        void clearDirty();
    protected:
        u32 bits_pack_;
        VertexData* vd_;
        Index geom_id_;
    };

}

#include "GeomStateBase.inl"
#endif //GEOMSTATEBASE_H
