#ifndef GEOMSTATES_H
#define GEOMSTATES_H

#include "../geom_enums.h"

namespace grynca {

    // fw
    class GeomState;
    class GeomStateBase;
    class VertexData;

    class GeomStates {
    public:
        GeomStates(VertexData& vd);

        template <typename T>
        void initStateType(GeomStateType id);

        VertexData& getVertexData()const;

        u32 getStatesCount(GeomStateType type_id)const;
        const GeomStateBase* getState(GeomStateType type_id, u32 id)const;
        GeomStateBase* accState(GeomStateType type_id, u32 id);
        GeomStateBase* addState(GeomStateType type_id, Index geom_id);
        void removeState(GeomStateType type_id, u32 id);


        u32 getDirtyStatesCount(GeomStateType type_id)const ;
        void clearDirtyStates(GeomStateType type_id);
        const GeomStateBase* getDirtyState(GeomStateType type_id, u32 dirty_id)const;
        GeomStateBase* accDirtyState(GeomStateType type_id, u32 dirty_id);

    private:
        friend class GeomStateBase;

        typedef void (*GeomStateConstr) (void* /*geomstate*/, const GeomStateType& /*type_id*/, VertexData&, const Index& /*geom_id*/);

        u32 getStateId_(GeomStateType type_id, const void* state_ptr)const;   // called by GeomStateBase

        VertexData* vd_;

        fast_vector<u8> states_[gstCount];
        fast_vector<u32> dirty_[gstCount];
        TypeInfo type_info_[gstCount];
        GeomStateConstr constructors_[gstCount];
    };

}

#include "GeomStates.inl"
#endif //GEOMSTATES_H
