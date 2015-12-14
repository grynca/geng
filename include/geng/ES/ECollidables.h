#ifndef ECOLLIDABLE_H
#define ECOLLIDABLE_H

#include <stdint.h>
#include "maths.h"
#include "types/Index.h"
#include "SAP.h"
#include "GengEntityRoles.h"
#include "../physics/Collidable.h"

namespace grynca {

    class ECollidables : public virtual GengEntity {
    public:
        ECollidables() : sap_(NULL), sap_id_(Index::Invalid()) {
            addRoles({GengEntityRoles::erCollidable});
        }

        ~ECollidables() {
            if (sap_id_ != Index::Invalid()) {
                sap_->removeBox(sap_id_);
            }
        }

        void recalcBound() {
            // TODO: recalc
        }

        // bound in local coords
        ARect& getBound() {
            return bound_;
        }

        uint32_t getCollisionGroup() { return collision_group_; }
    private:
        template <typename> friend class CollisionSystem;

        SAPManager<VersionedIndex, 2>* sap_;
        uint32_t sap_id_;

        ARect bound_;
        uint32_t collision_group_;
        fast_vector<Collidable> collidables_;
        //fast_vector<Collision> collisions_;
    };

}


#endif //ECOLLIDABLE_H
