#ifndef EMOVABLE_H
#define EMOVABLE_H

#include "ENonMovable.h"
#include "../physics/Speed.h"

namespace grynca {

    class EMovable : public ENonMovable {
    public:
        Speed& getSpeed() {
            return speed_;
        }

    private:

        Speed speed_;
    };

}

#endif //EMOVABLE_H
