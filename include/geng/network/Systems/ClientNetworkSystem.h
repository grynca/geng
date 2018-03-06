#ifndef CLIENTNETWORKSYSTEM_H
#define CLIENTNETWORKSYSTEM_H

#include "geng/core/GengSystem.h"
#include "geng/GERoles.h"
#include "../ClientStateBase.h"
#include "../Snapshots.h"
#include "ggnet.h"
#include <unordered_map>


namespace grynca {

    /* TODO:
     *  prepsat z post/pre update do novyho update stylu
     *  FIXNOUT SERIALIZACI/DESERIALIZACI s novym entity data layoutem
     * updatu muze pro jednu entitu prijit vic za tick
     * takze si je asi do mapy ulozim vsechny (pokud jsou delta ) - kdyz prijde full update, zahodim ostatni
     * potom je projdu od konce a pamatuju si ktery fieldy jsem updatoval v nejakej bitmasce
     * updatuju jen vzdycky nejnovejsi
    */

    class ClientNetworkSystem : public GengSystemAll {
    public:
        template <typename ClientStateType>     // must be derived from ClientStateBase & have default constructor
        void init();

        virtual RolesMask NeededRoles() override{
            return GERoles::erNetworkedClMask();
        }

        virtual void update(f32 dt, EntitiesList& entities) override;

        ClientStateBase& getClientState() { return *client_state_; }
    private:
        typedef std::unordered_map<EntityIndex /*server ent_id*/, EntityIndex /*client ent_id*/, Hasher<EntityIndex>> EntityIdsMap;

        Message encodeDeltaClientState_(ClientStateSnapshot& old_ss, ClientStateSnapshot& new_ss);
        Message encodeFullClientState_(ClientStateSnapshot& ss);

        Client* client_;

        ClientStateBase* client_state_;
        Fields client_state_fields_;
        ClientStateSnapshots client_state_snapshots_;
        DeltaSerializer delta_serializer_;

        EntityIdsMap entity_updates_;
    };

}

#include "ClientNetworkSystem.inl"
#endif //CLIENTNETWORKSYSTEM_H
