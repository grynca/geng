#ifndef SPEED_H
#define SPEED_H

#include "maths/Angle.h"
#include "maths/Vec2.h"

namespace grynca {

    class Speed {
    public:
        Speed() : angular_speed_(0), linear_speed_(0, 0), scalar_speed_(0, 0) {}

        Angle getAngularSpeed()const { return angular_speed_; }
        const Vec2& getLinearSpeed()const { return linear_speed_; }
        const Vec2& getScalarSpeed()const { return scalar_speed_; }
        void setAngularSpeed(const Angle& as) {
            angular_speed_ = as;
            flags_[fAngularSpeed] = (as != 0);
        }
        void setLinearSpeed(const Vec2& ls) {
            linear_speed_ = ls;
            flags_[fLinearSpeed] = !ls.isZero();
        }
        void setScalarSpeed(const Vec2& ss) {
            scalar_speed_ = ss;
            flags_[fScalarSpeed] = !ss.isZero();
        }

        bool hasAngularSpeed() { return flags_[fAngularSpeed]; }
        bool hasLinearSpeed() { return flags_[fLinearSpeed]; }
        bool hasScalarSpeed() { return flags_[fScalarSpeed]; }

    private:
        enum {
            fAngularSpeed,
            fLinearSpeed,
            fScalarSpeed
        };

        Angle angular_speed_;
        Vec2 linear_speed_;
        Vec2 scalar_speed_;
        std::bitset<8> flags_;
    };
}

#endif //SPEED_H
