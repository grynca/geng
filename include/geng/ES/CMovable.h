#ifndef CMOVABLE_H
#define CMOVABLE_H

#include "CTransform.h"
#include "../physics/Speed.h"

namespace grynca {

    class CMovable {
    public:
        static RolesMask componentRoles() {
            return {GengEntityRoles::erMovable};
        }

        Speed& getSpeed() {
            return speed_;
        }

    private:
        Speed speed_;
    };

}

#endif //CMOVABLE_H
