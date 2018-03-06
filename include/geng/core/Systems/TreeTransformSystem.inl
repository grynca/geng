#include <geng.h>
#include "TreeTransformSystem.h"

namespace grynca {

    inline void TreeTransformSystem::init() {
        subscribeFlags(this, GEFlags::fEntityMovedMask() | GEFlags::fEntityRotatedMask() | GEFlags::fEntityScaledMask() | GEFlags::fEntityTransformedMask());
    }

    inline void TreeTransformSystem::recieve(EntityFlagCtx& efctx) {
        // entity moved -> descendants' global transform becomes dirty
        CTreeTransformData* cttd = efctx.entity.getData<CTreeTransformData>();
        if (!GET_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform)) {
            EntityManager& emgr = getEntityManager();
            for (u32 i=0; i< cttd->children_count; ++i) {
                scheduleGlTransformUpdateRec_(emgr, cttd->children[i]);
            }
        }

        // also dirty local transform
        if (!GET_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform)) {
            scheduled_local_tr_update_.push_back(efctx.entity);
            cttd->flags = SET_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform);
        }

        // this permits this flag to be recieved again for this entity
        efctx.entity.clearTrackedFlagsForSystem(this);
    }

    inline void TreeTransformSystem::update(f32 dt, EntitiesList& entities) {
        EntityManager& emgr = getEntityManager();
        // update global transforms in tree
        for (u32 d=0; d<scheduled_global_tr_update_.size(); ++d) {
            for (u32 i=0; i<scheduled_global_tr_update_[d].size(); ++i) {
                Entity& e = scheduled_global_tr_update_[d][i];
                CTransformData* ctd = e.getData<CTransformData>();
                CTreeTransformData* cttd = e.getData<CTreeTransformData>();

                Entity parent = emgr.getEntity(cttd->parent_id);
                CTransformData* parent_ct = parent.getData<CTransformData>();
                ctd->set(*parent_ct * cttd->local_transform);
                cttd->flags = CLEAR_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform);
                //notify following systems that entity global transform has changed
                e.setFlag(GEFlags::fEntityTransformedId, this->getSystemPos());
            }
            scheduled_global_tr_update_[d].clear();
        }

        // update local transforms
        for (u32 i=0; i<scheduled_local_tr_update_.size(); ++i) {
            Entity& e = scheduled_local_tr_update_[i];

            CTreeTransformData* cttd = e.getData<CTreeTransformData>();
            if (GET_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform)) {
                CTransformData* ctd = e.getData<CTransformData>();

                if (cttd->parent_id.isValid()) {
                    Entity parent = emgr.getEntity(cttd->parent_id);
                    CTransformData* parent_ct = parent.getData<CTransformData>();
                    cttd->local_transform.set(*ctd - *parent_ct);
                }
                else {
                    cttd->local_transform.set(*ctd);
                }
                cttd->flags = CLEAR_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform);
            }
        }
        scheduled_local_tr_update_.clear();
    }

    inline void TreeTransformSystem::checkMaxDepth(u32 depth) {
        if (depth>scheduled_global_tr_update_.size()) {
            scheduled_global_tr_update_.enlarge(depth+1);
        }
    }

    inline void TreeTransformSystem::scheduleGlTransformUpdateRec_(EntityManager &emgr, EntityIndex eid) {
        Entity e = emgr.getEntity(eid);
        CTreeTransformData* cttd = e.getData<CTreeTransformData>();
        if (!GET_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform)) {
            cttd->flags = SET_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform);
            scheduled_global_tr_update_[cttd->depth].push_back(e);
            for (u32 i=0; i< cttd->children_count; ++i) {
                scheduleGlTransformUpdateRec_(emgr, cttd->children[i]);
            }
        }
    }

}