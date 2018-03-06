#ifndef ROTATION_UTILS_H
#define ROTATION_UTILS_H

#include "maths/Angle.h"

namespace grynca {
    namespace physics {

        // returns ang. speed
        inline static Angle controlAngSpeed(Angle a_curr, Angle a_to, f32 max_angular_speed, f32 upd_dt = 1.0f/60) {
            ASSERT(max_angular_speed > 0.0f);

            Angle delta = (a_to - a_curr).normalize();
            f32 max_tick_delta = max_angular_speed*upd_dt;
            f32 ratio = fabsf(delta.getRads())/max_tick_delta;
            ratio = std::min(1.0f, ratio);
            return delta*ratio;
        }

        // returns angle
        inline static Angle motAngleWithSpeed(Angle a_curr, Angle a_to, f32 rot_speed, f32 upd_dt = 1.0f/60) {
            ASSERT(rot_speed > 0.0f);

            f32 dir = sgn((a_to-a_curr).normalize().getRads());
            return std::max(a_to, a_curr+dir*rot_speed*upd_dt);
        }

        // returns angle
        inline static Angle motAngleWithTime(Angle a_curr, Angle a_to, f32 rot_time, f32 upd_dt = 1.0f/60) {
            ASSERT(rot_time > 0.0f);

            f32 rot_speed = (a_to - a_curr).normalize().getRads()/rot_time;
            return a_curr+rot_speed*upd_dt;
        }

        // returns new pos
        inline static Vec2 motPosWithSpeed(const Vec2& p_curr, const Vec2& p_to, f32 move_speed, f32 upd_dt = 1.0f/60) {
            ASSERT(move_speed > 0.0f);

            Vec2 to_target = p_to - p_curr;
            f32 dist = to_target.getLen();
            f32 speed = move_speed*upd_dt;
            if (dist > speed) {
                to_target /= dist;
                to_target *= speed;
            }
            return p_curr + to_target;
        }

        // returns new pos
        inline static Vec2 motPosWithTime(const Vec2& p_curr, const Vec2& p_to, f32 move_time, f32 upd_dt = 1.0f/60) {
            ASSERT(move_time > 0.0f);

            Vec2 move_speed = (p_to-p_curr)/move_time;
            return p_curr + move_speed*upd_dt;
        }
    }
}

#endif //ROTATION_UTILS_H
