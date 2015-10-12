#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types/Type.h"

namespace grynca {

    class GraphicsDomain {
    public:
        static void setIds();

        template <typename T>
        static uint32_t getTypeId() {
            return Type<T, GraphicsDomain>::getTypeInfo().getId();
        }
    };
}

#endif //GRAPHICS_H
