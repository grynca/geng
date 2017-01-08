#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <bitset>
#include "sysent/Entity.h"

#define DEF

namespace grynca {

    template <typename...CompTypes>
    class GengEntityDef : public EntityDef<CompTypes...> {
    public:
        static u32& typeId() {
            static u32 tid = InvalidId();
            return tid;
        }
    };

}

#endif //GAMEENTITY_H
