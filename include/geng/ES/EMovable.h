#ifndef EMOVABLE_H
#define EMOVABLE_H

#include "ETransform.h"
#include "../physics/Speed.h"

namespace grynca {

    class EMovable : public ETransform {
    public:
        EMovable() {
            addRoles({GengEntityRoles::erMovable});
        }
        Speed& getSpeed() {
            return speed_;
        }

    private:
        Speed speed_;
    };

}

#endif //EMOVABLE_H
