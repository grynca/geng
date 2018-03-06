#ifndef ENTITYRESOURCES_H
#define ENTITYRESOURCES_H
#include "types/Manager.h"

#define WITHOUT_IMPL
#   include "../Game.h"
#undef WITHOUT_IMPL

namespace grynca {

    // fw
    class EntityResourcesManager;

    class EntityResourcesBase : public ManagedItemSingleton<EntityResourcesManager> {
    public:
    };

    class EntityResourcesManager : public ManagerSingletons<EntityResourcesBase> {
    public:
        ~EntityResourcesManager() {}
    };

    template <typename Derived>
    class EntityResources : public EntityResourcesBase {
    public:
        static Derived& get() {
            return GameBase::get().accModule<EntityResourcesManager>().getFast<Derived>();
        }
    };
}

#endif //ENTITYRESOURCES_H
