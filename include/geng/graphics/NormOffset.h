#ifndef NORMOFFSET_H
#define NORMOFFSET_H

#include "maths/Vec2.h"

namespace grynca {

    class NormOffset {
    public:
        enum Type {
            otLeftTop,
            otRightTop,
            otRightBot,
            otLeftBot,
            otCenter,
            otLeftCenter,
            otTopCenter,
            otRightCenter,
            otBottomCenter,

            otCount
        };

        static const Vec2& get(Type offset_type) {
            // static
            static Vec2 offsets[otCount] = {
                    {0,0},          //otLeftTop
                    {-1, 0},        //otRightTop
                    {-1, -1},       //otRightBot
                    {0, -1},        //otLeftBot
                    {-0.5f, -0.5f}, //otCenter
                    {0, -0.5f},     //otLeftCenter
                    {-0.5f, 0},     //otTopCenter
                    {-1, -0.5f},    //otRightCenter
                    {-0.5f, -1}     //otBottomCenter
            };
            return offsets[offset_type];
        }
    };
}

#endif //NORMOFFSET_H
