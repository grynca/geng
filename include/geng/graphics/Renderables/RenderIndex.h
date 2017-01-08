#ifndef RENDER_INDEX_H
#define RENDER_INDEX_H

#include "maths/Vec2.h"

namespace grynca {

    class NormOffset {
    public:
        static Vec2 Center() { return Vec2{-0.5f, -0.5f}; };
        static Vec2 LeftTop() { return Vec2{0,0}; }
        static Vec2 RightTop() { return Vec2{-1, 0}; }
        static Vec2 RightBot() { return Vec2{-1, -1}; }
        static Vec2 LeftBot() { return Vec2{0, -1}; }
    };

    class RenderIndex {
    public:
        RenderIndex(u32 val);
        RenderIndex();

        bool getVisible()const;
        u16 getLayerId()const;
        u16 getShaderId()const;
        u16 getVertexLayoutId()const;
        u16 getVertexBufferId()const;

        void setVisible(bool value);
        void setLayerId(u16 layer_id);
        void setShaderId(u16 shader_id);
        void setVertexLayoutId(u16 vl_id);
        void setVertexBufferId(u16 vb_id);

        u32 getAsInt()const;
    protected:
        u32 pack_id_;
    };
}

#include "RenderIndex.inl"
#endif //RENDER_INDEX_H
