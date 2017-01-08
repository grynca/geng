#include "RenderIndex.h"
#include "../graphics_config.h"
#include <cassert>

#define VERT_BUFFER_BITS_START 0
#define VERT_LAYOUT_BITS_START VERT_BUFFER_BITS_START + config::VBO_BITS
#define SHADER_BITS_START VERT_LAYOUT_BITS_START+config::VERT_LAYOUT_BITS
#define LAYER_BITS_START SHADER_BITS_START+config::SHADER_BITS
#define VISIBILITY_BIT LAYER_BITS_START+config::LAYER_BITS

namespace grynca {

    inline RenderIndex::RenderIndex(u32 val)
     : pack_id_(val)
    {}

    inline RenderIndex::RenderIndex()
     : pack_id_(0)
    {
    }

    inline bool RenderIndex::getVisible()const {
        return !GET_BIT(pack_id_, VISIBILITY_BIT);
    }

    inline u16 RenderIndex::getLayerId()const {
        return u16(GET_BITS(pack_id_, LAYER_BITS_START, config::LAYER_BITS));
    }

    inline u16 RenderIndex::getShaderId()const {
        return u16(GET_BITS(pack_id_, SHADER_BITS_START, config::SHADER_BITS));
    }

    inline u16 RenderIndex::getVertexLayoutId()const {
        return u16(GET_BITS(pack_id_, VERT_LAYOUT_BITS_START, config::VERT_LAYOUT_BITS));
    }

    inline u16 RenderIndex::getVertexBufferId()const {
        return u16(GET_BITS(pack_id_, VERT_BUFFER_BITS_START, config::VBO_BITS));
    }

    inline void RenderIndex::setVisible(bool value) {
        pack_id_ = SET_BITV(pack_id_, VISIBILITY_BIT, !value);
    }

    inline void RenderIndex::setLayerId(u16 layer_id) {
        ASSERT(layer_id < config::MAX_LAYERS);
        pack_id_ = SET_BITS(pack_id_, LAYER_BITS_START, config::LAYER_BITS, layer_id);
    }

    inline void RenderIndex::setShaderId(u16 shader_id) {
        ASSERT(shader_id < config::MAX_SHADERS);
        pack_id_ = SET_BITS(pack_id_, SHADER_BITS_START, config::SHADER_BITS, shader_id);
    }

    inline void RenderIndex::setVertexLayoutId(u16 vl_id) {
        ASSERT(vl_id < config::MAX_VERTEX_LAYOUTS);
        pack_id_ = SET_BITS(pack_id_, VERT_LAYOUT_BITS_START, config::VERT_LAYOUT_BITS, vl_id);
    }

    inline void RenderIndex::setVertexBufferId(u16 vb_id) {
        ASSERT(vb_id < config::MAX_VBOS);
        pack_id_ = SET_BITS(pack_id_, VERT_BUFFER_BITS_START, config::VBO_BITS, vb_id);
    }

    inline u32 RenderIndex::getAsInt()const {
        return pack_id_;
    }

}
#undef LAYER_BITS_START
#undef SHADER_BITS_START
#undef VERT_LAYOUT_BITS_START
#undef VERT_BUFFER_BITS_START
#undef VISIBILITY_BIT