#include "BoundsSystem.h"

namespace grynca {

    inline void BoundsSystem::init() {
        pm_ = &getGame().accPhysicsManager();

        // bound should be rotation invariant, so we dont care about entity rotation
        auto fm_bound_updated = GEFlags::fEntityScaledMask() | GEFlags::fEntityRotatedMask() | GEFlags::fBoundChangedMask() | GEFlags::fEntityTransformedMask();
        subscribeFlags(this, GEFlags::fEntityMovedMask() | fm_bound_updated);
        update_bound_fm_ = calcFlagsMaskLong(fm_bound_updated);
    }

    inline void BoundsSystem::recieve(EntityFlagCtx& efctx) {
        scheduleEntityUpdate(efctx.entity);
    }

    inline void BoundsSystem::onEntityAdded(Entity &e, bool by_roles_change) {
        CColliderData* cco = e.getData<CColliderData>();
        CTransformData* ctd = e.getData<CTransformData>();
        ASSERT(!cco->getSapId().isValid());
        // add to SAP
        pm_->addCollider(*cco, *ctd, e.getIndex().getInnerIndex());
    }

    inline void BoundsSystem::onEntityRemoved(Entity &e, bool by_roles_change) {
        CColliderData* cco = e.getData<CColliderData>();
        ASSERT(cco->getSapId().isValid());
        // remove from SAP
        pm_->removeCollider(*cco);
    }

    inline void BoundsSystem::update(f32 dt, EntitiesList& entities) {
        entities.loopEntities([this, dt](Entity& e) {
            CColliderData* cco = e.getData<CColliderData>();
            CTransformData* ctd = e.getData<CTransformData>();

            if ((e.getFlags()&update_bound_fm_).any()) {
                // transform bound
                pm_->updateCollider(*cco, *ctd);
            }
            else {
                ASSERT(e.getFlag(GEFlags::fEntityMovedId));
                // move with box
                ARect prev_rect((Vec2*)pm_->accSAP().getBox(cco->getSapId()).getBounds());
                Vec2 curr_center(ctd->calcMatrix() * cco->getBoundARect().getCenter());
                Vec2 move_vec = curr_center - prev_rect.getCenter();
                pm_->moveCollider(*cco, move_vec);
            }
        });
    }
}