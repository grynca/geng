#ifndef RENDER_BATCH_ID_H
#define RENDER_BATCH_ID_H

#include "maths/Vec2.h"

namespace grynca {

    // index for render sorting
    // MSB [layer_id, shader_id, vert_layout_id, vbo_id]
    class RenderBatchId {
    public:
        RenderBatchId(u32 val);
        RenderBatchId();

        u16 getLayerId()const;
        u16 getShaderId()const;
        u16 getVertexLayoutId()const;
        u16 getVertexBufferId()const;

        void setLayerId(u16 layer_id);
        void setShaderId(u16 shader_id);
        void setVertexLayoutId(u16 vl_id);
        void setVertexBufferId(u16 vb_id);
        u32 getAsInt()const;
    protected:
        u32 pack_id_;
    };
}

#include "RenderBatchId.inl"
#endif //RENDER_BATCH_ID_H
