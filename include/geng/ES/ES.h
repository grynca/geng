#ifndef ES_H
#define ES_H

#include "sysent.h"

namespace grynca {

    template <typename EntityTypes,
              typename UpdateSystemTypes,
              typename RenderSystemTypes>
    class ES
    {
    public:
        ES(uint32_t ents_initial_reserve)
         : entity_manager_(ents_initial_reserve), update_systems_(entity_manager_), render_systems_(entity_manager_)
        {}

        ES()
         : update_systems_(entity_manager_), render_systems_(entity_manager_)
        {}

        EntityManager<EntityTypes>& getEntityManager() { return entity_manager_; }
        SystemManager<EntityTypes, UpdateSystemTypes>& getUpdateSystemsManager() { return update_systems_; }
        SystemManager<EntityTypes, RenderSystemTypes>& getRenderSystemsManager() { return render_systems_; }

    private:
        EntityManager<EntityTypes> entity_manager_;
        SystemManager<EntityTypes, UpdateSystemTypes> update_systems_;
        SystemManager<EntityTypes, RenderSystemTypes> render_systems_;
    };


}

#endif //ES_H
