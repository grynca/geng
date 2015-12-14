#ifndef ES_H
#define ES_H

#include "sysent.h"

namespace grynca {

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    class ES
    {
    public:
        using EntityTypes = ETs;
        using UpdateSystemTypes = USTs;
        using RenderSystemTypes = RSTs;
        using EntityRoles = ERs;
        using EntityManagerType = EntityManager<EntityTypes>;
        using UpdateSystemManagerType = SystemManager<EntityTypes, UpdateSystemTypes>;
        using RenderSystemManagerType = SystemManager<EntityTypes, RenderSystemTypes>;

        ES(uint32_t ents_initial_reserve)
         : entity_manager_(ents_initial_reserve), update_systems_(entity_manager_), render_systems_(entity_manager_)
        {}

        ES()
         : update_systems_(entity_manager_), render_systems_(entity_manager_)
        {}

        EntityManagerType& getEntityManager() { return entity_manager_; }
        UpdateSystemManagerType& getUpdateSystemsManager() { return update_systems_; }
        RenderSystemManagerType& getRenderSystemsManager() { return render_systems_; }

    private:
        EntityManagerType entity_manager_;
        UpdateSystemManagerType update_systems_;
        RenderSystemManagerType render_systems_;
    };


}

#endif //ES_H
