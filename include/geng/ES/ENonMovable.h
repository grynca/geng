#ifndef ENONMOVABLE_H
#define ENONMOVABLE_H

#include "maths/Transform.h"

namespace grynca {

    class ENonMovable {
    public:
        Transform& getTransform() {
            return transform_;
        }
    private:
        Transform transform_;
    };

}

#endif //ENONMOVABLE_H
