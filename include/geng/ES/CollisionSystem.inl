#include "CollisionSystem.h"
#include "ECollidables.h"
#include "ES.h"

namespace grynca {

    template <typename GameType>
    void CollisionSystem<GameType>::update(GameEntity &e, float dt) {

        ECollidables & c = e.template getBase<ECollidables>();

        if (c.sap_id_ == Index::Invalid()) {
            c.recalcBound();
            Vec2 lt = c.getBound().getLeftTop();
            Vec2 rb = c.getBound().getRightBot();
            Extent extent[2] = {
                    {lt.getX(), rb.getX()},
                    {lt.getY(), rb.getY()}
            };

            // add box
            c.sap_ = &sap_;
            c.sap_id_ = sap_.addBox(extent, c.getCollisionGroup(), e.getId());
        }
        else if (c.getFlags()[GengEntity::fRotated]) {
            c.recalcBound();
            Vec2 lt = c.getBound().getLeftTop();
            Vec2 rb = c.getBound().getRightBot();
            Extent extent[2] = {
                    {lt.getX(), rb.getX()},
                    {lt.getY(), rb.getY()}
            };
            sap_.updateBox(c.sap_id_, extent);
        }
        else if (c.getFlags()[GengEntity::fMoved]) {
            ETransform& t = e.template getBase<ETransform>();
            Vec2 lt = t.getTransform().getPosition() + c.getBound().getLeftTop();
            Vec2 rb = lt + c.getBound().getSize();
            Extent extent[2] = {
                    {lt.getX(), rb.getX()},
                    {lt.getY(), rb.getY()}
            };
            sap_.updateBox(c.sap_id_, extent);
        }
    }

    template <typename GameType>
    inline void CollisionSystem<GameType>::postUpdate() {
        for (uint32_t i=0; i<sap_.getBoxesCount(); ++i) {
            uint32_t b1_id;
            const fast_vector<uint32_t>& overlaps = sap_.getOverlapsAtPos(i, b1_id);
            // todo: simple or precise feedback
            VersionedIndex eid1 = sap_.getClientData(b1_id);
            GameEntity& e1 = this->getGameBase().getSysEnt().getEntityManager().getItem(eid1);
            ECollidables& c1 = e1.template getBase<ECollidables>();
            for (uint32_t oid=0; oid<overlaps.size(); ++oid) {
                VersionedIndex eid2 = sap_.getClientData(overlaps[oid]);
                GameEntity& e2 = this->getGameBase().getSysEnt().getEntityManager().getItem(eid2);
                ECollidables& c2 = e2.template getBase<ECollidables>();


            }
        }
    }

}