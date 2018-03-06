#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <bitset>
#include "sysent/Entity.h"
#include "EntityResourcesManager.h"

namespace grynca {

    // fw
    class GameBase;

    template <typename...CompTypes>
    class GengEntityDef : public EntityDef<CompTypes...> {
        typedef EntityDef<CompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(GengEntityDef);

        // dummy empty resources
        class Resources : public EntityResources<Resources> {
        public:
            void initSingleton(GameBase&) {}
        };

        // default no-ops
        // meant to be statically overriden by derivate class
        void onKilled() {}
    };
}

#endif //GAMEENTITY_H
