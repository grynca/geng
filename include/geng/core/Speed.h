#ifndef SPEED_H
#define SPEED_H

#include "maths/Angle.h"
#include "maths/Vec2.h"

namespace grynca {

    class Speed {
    public:
        Speed() : angular_speed_(0), linear_speed_(0, 0) {}

        Angle getAngularSpeed()const { return angular_speed_; }
        const Vec2& getLinearSpeed()const { return linear_speed_; }
        void setAngularSpeed(const Angle& as) { angular_speed_ = as; }
        void setLinearSpeed(const Vec2& ls) { linear_speed_ = ls; }
        Angle& accAngularSpeed() { return angular_speed_; }
        Vec2& accLinearSpeed() { return linear_speed_; }
    private:
        Angle angular_speed_;
        Vec2 linear_speed_;
    };
}

#endif //SPEED_H
