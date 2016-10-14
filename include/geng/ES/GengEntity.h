#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <bitset>
#include "sysent/Entity.h"
namespace grynca {


    template <typename...CompTypes>
    class GengEntityDef : public EntityDef<CompTypes...> {
    };

}

#endif //GAMEENTITY_H
