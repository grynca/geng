#include "CollisionSystem.h"
#include "../Components/CBody.h"
#include "../../core/Components/CTransform.h"

namespace grynca {

    inline void CollisionSystem::afterAddedEntity(Entity& e)  {
        CBody& cb = e.getComponent<CBody>();
        cb.recalcBound();
        CTransform& ct = e.getComponent<CTransform>();
        ARect bound = cb.transformBound(ct.get().calcMatrix());
        cb.sap_id_ = sap_.addBox(bound.getDataPtr(), e.getIndex());
    }

    inline void CollisionSystem::beforeRemovedEntity(Entity& e)  {
        CBody & c = e.getComponent<CBody>();
        sap_.removeBox(c.sap_id_);
    }

    inline void CollisionSystem::updateEntity(Entity& e, float dt) {
        if (e.getFlag(this, GEFlags::fRotScaledId)) {
            CBody& cb = e.getComponent<CBody>();
            CTransform& ct = e.getComponent<CTransform>();
            ARect bound = cb.transformBound(ct.get().calcMatrix());
            sap_.updateBox(cb.sap_id_, bound.getDataPtr());
        }
        else if (e.getFlag(this, GEFlags::fMovedId)) {
            CBody& cb = e.getComponent<CBody>();
            CTransform& ct = e.getComponent<CTransform>();

            ARect prev_rect;
            sap_.getBox(cb.sap_id_, prev_rect.getDataPtr());
            Vec2 curr_center(ct.get().calcMatrix() * cb.getBound().getCenter());
            Vec2 move_vec = curr_center - prev_rect.getCenter();
            sap_.moveBox(cb.sap_id_, move_vec.getDataPtr());
        }
    }

    inline void CollisionSystem::postUpdate(f32 dt) {

        //std::cout << "overlaps:" << sap_.getOverlapsCount() << std::endl;
//        for (u32 i=0; i<sap_.getBoxesCount(); ++i) {
//            u32 b1_id;
//            const fast_vector<u32>& overlaps = sap_.getOverlapsAtPos(i, b1_id);
//            // todo: simple or precise feedback
//            EntityIndex eid1 = sap_.getClientData(b1_id);
//            Entity e1 = this->getGameBase().getEntity(eid1);
//            CBody& c1 = e1.getComponent<CBody>();
//            for (u32 oid=0; oid<overlaps.size(); ++oid) {
//                EntityIndex eid2 = sap_.getClientData(overlaps[oid]);
//                Entity e2 = this->getGameBase().getEntity(eid2);
//                CBody& c2 = e2.getComponent<CBody>();
//                // TODO:
//            }
//        }
    }

}