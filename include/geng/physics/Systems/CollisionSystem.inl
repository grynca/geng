#include "CollisionSystem.h"
#include "../Components/CBody.h"
#include "../../core/Components/CTransform.h"

namespace grynca {

    template <typename GameType>
    inline void CollisionSystem<GameType>::afterAddedEntity(Entity& e)  {
        CBody& cb = e.getComponent<CBody>();
        cb.recalcBound();
        CTransform& ct = e.getComponent<CTransform>();
        ARect bound = cb.transformBound(ct.accMatrix());
        cb.sap_id_ = sap_.addBox(bound.getDataPtr(), e.getIndex());
    }

    template <typename GameType>
    inline void CollisionSystem<GameType>::beforeRemovedEntity(Entity& e)  {
        CBody & c = e.getComponent<CBody>();
        sap_.removeBox(c.sap_id_);
    }

    template <typename GameType>
    inline void CollisionSystem<GameType>::updateEntity(Entity& e, float dt) {
        // TODO: fScaled
        if (e.getFlag(this, GengEntityFlags::fRotated)) {
            CBody& cb = e.getComponent<CBody>();
            CTransform& ct = e.getComponent<CTransform>();
            ARect bound = cb.transformBound(ct.accMatrix());
            sap_.updateBox(cb.sap_id_, bound.getDataPtr());
        }
        else if (e.getFlag(this, GengEntityFlags::fMoved)) {
            CBody& cb = e.getComponent<CBody>();
            CTransform& ct = e.getComponent<CTransform>();

            ARect prev_rect;
            sap_.getBox(cb.sap_id_, prev_rect.getDataPtr());
            Vec2 curr_center(ct.accMatrix() * cb.getBound().getCenter());
            Vec2 move_vec = curr_center - prev_rect.getCenter();
            sap_.moveBox(cb.sap_id_, move_vec.getDataPtr());
        }
    }

    template <typename GameType>
    inline void CollisionSystem<GameType>::postUpdate() {

        //std::cout << "overlaps:" << sap_.getOverlapsCount() << std::endl;
//        for (uint32_t i=0; i<sap_.getBoxesCount(); ++i) {
//            uint32_t b1_id;
//            const fast_vector<uint32_t>& overlaps = sap_.getOverlapsAtPos(i, b1_id);
//            // todo: simple or precise feedback
//            EntityIndex eid1 = sap_.getClientData(b1_id);
//            Entity e1 = this->getGameBase().getEntity(eid1);
//            CBody& c1 = e1.getComponent<CBody>();
//            for (uint32_t oid=0; oid<overlaps.size(); ++oid) {
//                EntityIndex eid2 = sap_.getClientData(overlaps[oid]);
//                Entity e2 = this->getGameBase().getEntity(eid2);
//                CBody& c2 = e2.getComponent<CBody>();
//                // TODO:
//            }
//        }
    }

}