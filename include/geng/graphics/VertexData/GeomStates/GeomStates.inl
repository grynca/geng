#include "GeomStates.h"
#include "GeomStateBase.h"
#include "types/containers/Items2.h"
#include "types/Index.h"

#define ITEMS Items2Ref<> items(const_cast<GeomStates*>(this)->states_[type_id], type_info_[type_id]);

namespace grynca {

    inline GeomStates::GeomStates(VertexData& vd)
     : vd_(&vd)
    {
        memset(constructors_, 0, sizeof(constructors_));
        memset(type_info_, 0, sizeof(type_info_));
    }

    template <typename T>
    inline void GeomStates::initStateType(GeomStateType type_id) {
        TypeInfoManager<GeomStates>::setTypeId<T>(type_id);
        type_info_[type_id] = Type<T, GeomStates>::getTypeInfo();
        constructors_[type_id] = Type<T>::template create2<const GeomStateType&, VertexData&, const Index&>;
    }

    inline VertexData& GeomStates::getVertexData()const {
        return *vd_;
    }

    inline u32 GeomStates::getStatesCount(GeomStateType type_id)const {
        ITEMS;
        return items.size();
    }

    inline const GeomStateBase* GeomStates::getState(GeomStateType type_id, u32 id)const {
        ITEMS;
        return (const GeomStateBase*)items.getItemPtr(id);
    }

    inline GeomStateBase* GeomStates::accState(GeomStateType type_id, u32 id) {
        ITEMS;
        return (GeomStateBase*)items.getItemPtr(id);
    }

    inline GeomStateBase* GeomStates::addState(GeomStateType type_id, Index geom_id) {
        ITEMS;
        u8* pos = items.push_back2();
        constructors_[type_id](pos, type_id, getVertexData(), geom_id);
        return (GeomStateBase*)pos;
    }

    inline void GeomStates::removeState(GeomStateType type_id, u32 id) {
        ITEMS;
        GeomStateBase* gs = (GeomStateBase*)items.replaceWithLast(id);
        gs->accGeom().setStateId_(id);
    }

    inline u32 GeomStates::getDirtyStatesCount(GeomStateType type_id)const {
        return u32(dirty_[type_id].size());
    }

    inline void GeomStates::clearDirtyStates(GeomStateType type_id) {
        dirty_[type_id].clear();
    }

    inline const GeomStateBase* GeomStates::getDirtyState(GeomStateType type_id, u32 dirty_id)const {
        u32 state_id = dirty_[type_id][dirty_id];
        return getState(type_id, state_id);
    }

    inline GeomStateBase* GeomStates::accDirtyState(GeomStateType type_id, u32 dirty_id) {
        u32 state_id = dirty_[type_id][dirty_id];
        return accState(type_id, state_id);
    }

    inline u32 GeomStates::getStateId_(GeomStateType type_id, const void* state_ptr)const {
        return (((u8*)state_ptr) - &states_[type_id][0]) / type_info_[type_id].getSize();
    }

}

#undef ITEMS