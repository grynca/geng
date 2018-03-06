#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include "functions/meta.h"
#include "maths/Angle.h"

namespace grynca {
    namespace physics {

        // you should divide returned value by mass or something to be more physically accurate
        // dis... displacement from equilibrium
        template <typename ValType>
        inline static ValType spring(const ValType& dis, f32 tightness) {
            return -tightness*dis;
        }

        // you should divide returned value by mass or something to be more physically accurate
        // vel... velocity (when connected to static) or relative velocity between two dynamic points
        // increase dumping for object to come to rest more quickly
        template <typename ValType>
        inline static ValType springDump(const ValType& dis, const ValType& vel, f32 tightness, f32 dumping) {
            return -tightness*dis - dumping*vel;
        }

        /* use with combination with spring funcs:
         *   springDump(keepDistance(curr_dis, target_dis), vel, t, d);
         */

        inline static f32 keepDistance(f32 dis, f32 desired_dis) {
            return (fabsf(dis)-desired_dis)*sgn(dis);
        }

        // when you have precomputed dis_len
        inline static Vec2 keepDistance(const Vec2& dis, f32 dis_len, f32 desired_dis_len) {
            return (dis_len-desired_dis_len)*(dis/dis_len);
        }

        inline static Vec2 keepDistance(const Vec2& dis, f32 desired_dis_len) {
            return keepDistance(dis, dis.getLen(), desired_dis_len);
        }
    }
}

#endif //PHYSICS_UTILS_H
