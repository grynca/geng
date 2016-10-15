#ifndef CLIENTNETWORKSYSTEM_H
#define CLIENTNETWORKSYSTEM_H

#include "../../core/GengSystem.h"
#include "../../core/GengEntityRoles.h"
#include "../ClientStateBase.h"
#include "../Snapshots.h"
#include "ggnet.h"
#include <unordered_map>


namespace grynca {

    /* TODO:
     *  FIXNOUT SERIALIZACI/DESERIALIZACI s novym entity data layoutem
     * updatu muze pro jednu entitu prijit vic za tick
     * takze si je asi do mapy ulozim vsechny (pokud jsou delta ) - kdyz prijde full update, zahodim ostatni
     * potom je projdu od konce a pamatuju si ktery fieldy jsem updatoval v nejakej bitmasce
     * updatuju jen vzdycky nejnovejsi
    */

    template <typename GameType>
    class ClientNetworkSystem : public GengSystem<GameType> {
    public:
        template <typename ClientStateType>     // must be derived from ClientStateBase & have default constructor
        void init();

        virtual FlagsMask getTrackedFlags() override{
            return {};
        }
        virtual RolesMask getNeededRoles() override{
            return {GengEntityRoles::erNetworkedCl};
        }

        virtual void preUpdate() override;
        virtual void updateEntity(Entity& e, float dt) override;
        virtual void postUpdate() override;

        ClientStateBase<GameType>& getClientState() { return *client_state_; }
    private:
        typedef std::unordered_map<EntityIndex /*server ent_id*/, EntityIndex /*client ent_id*/, EntityIndex::Hasher> EntityIdsMap;

        Message encodeDeltaClientState_(ClientStateSnapshot& old_ss, ClientStateSnapshot& new_ss);
        Message encodeFullClientState_(ClientStateSnapshot& ss);

        Client* client_;

        ClientStateBase<GameType>* client_state_;
        Fields client_state_fields_;
        ClientStateSnapshots client_state_snapshots_;
        DeltaSerializer delta_serializer_;

        EntityIdsMap entity_updates_;
    };

}

#include "ClientNetworkSystem.inl"
#endif //CLIENTNETWORKSYSTEM_H