#ifndef CCOLLIDABLE_H
#define CCOLLIDABLE_H

#include <stdint.h>
#include "maths.h"
#include "types/Index.h"
#include "SAP.h"
#include "geng/GERoles.h"
#include "../Collidable.h"

namespace grynca {


    class CBody {
    public:
        static RolesMask componentRoles() {
            return GERoles::erCollidableMask();
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
            for (u32 i=1; i<collidables_.size(); ++i) {
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

        Collidable& addCollidable(u32& collidable_id_out) {
            collidable_id_out = collidables_.size();
            collidables_.emplace_back();
            return collidables_.back();
        }

        Collidable& addCollidable() {
            collidables_.emplace_back();
            return collidables_.back();
        }

        u32 getSapId() { return sap_id_; }
        //u32 getCollisionGroup() { return collision_group_; }
    private:
        friend class CollisionSystem;

        u32 sap_id_;
        Collidables collidables_;

        ARect bound_;
        //u32 collision_group_;
        //fast_vector<Collision> collisions_;
    };

}


#endif //CCOLLIDABLE_H
