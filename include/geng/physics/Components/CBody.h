#ifndef CCOLLIDABLE_H
#define CCOLLIDABLE_H

#include <stdint.h>
#include "maths.h"
#include "types/Index.h"
#include "SAP.h"
#include "../../core/GengEntityRoles.h"
#include "../Collidable.h"

namespace grynca {


    class CBody {
    public:

        static RolesMask componentRoles() {
            return {GengEntityRoles::erCollidable};
        }

        CBody()
         : sap_id_(InvalidId())
        {
        }

        // TODO: should be called each time collidables are modified
        //       ted vubec neberu v uvahu lokalni rotace collidablu
        //        - potrebuju je vubec ?
        void recalcBound() {
            ASSERT(!collidables_.empty());
            collidables_[0].recalcBound();
            bound_ = collidables_[0].getBound();
            for (uint32_t i=1; i<collidables_.size(); ++i) {
                collidables_[i].recalcBound();
                bound_.expand(collidables_[i].getBound());
            }
        }

        // bound in local coords
        ARect& getBound() {
            return bound_;
        }

        ARect transformBound(const Mat3& transform) {
            Vec2 pts[4] = {
                transform * bound_.getLeftTop(),
                transform * bound_.getRightTop(),
                transform * bound_.getRightBot(),
                transform * bound_.getLeftBot()
            };
            return ARect(&pts[0], 4);
        }

        Collidables& getCollidables() { return collidables_; }

        Collidable& addCollidable(uint32_t& collidable_id_out) {
            collidable_id_out = collidables_.size();
            collidables_.push_back();
            return collidables_.back();
        }

        Collidable& addCollidable() {
            collidables_.push_back();
            return collidables_.back();
        }

        uint32_t getSapId() { return sap_id_; }
        //uint32_t getCollisionGroup() { return collision_group_; }
    private:
        template <typename> friend class CollisionSystem;

        uint32_t sap_id_;
        Collidables collidables_;

        ARect bound_;
        //uint32_t collision_group_;
        //fast_vector<Collision> collisions_;
    };

}


#endif //CCOLLIDABLE_H
