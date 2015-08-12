#ifndef DRAWSORTINGKEY_H
#define DRAWSORTINGKEY_H

#include <stdint.h>

namespace grynca {

    struct DrawSortingKey {
        DrawSortingKey() : key(0) {}

        union {
            // layer_id|shader_id|vertex_layout_id|unused
            struct {
                uint16_t unused;
                uint16_t vertex_layout_id;
                uint16_t shader_id;
                uint16_t layer_id;
            };
            uint64_t key;
        };
    };

}

#endif //DRAWSORTINGKEY_H
