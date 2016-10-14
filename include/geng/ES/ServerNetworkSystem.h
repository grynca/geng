#ifndef SERVERNETWORKSYSTEM_H
#define SERVERNETWORKSYSTEM_H

#include "GengSystem.h"
#include "CNetworked.h"
#include "types/containers/SharedBuffer.h"
#include "../network/Snapshots.h"

namespace grynca {

    // fw
    class Server;

    // TODO:
    //  pridat do Server classy registraci callbacku na pripojeni a odpojeni clientu
    //  ActionsStateType bude mit clear() kterej budu volat v hadleru po pripojeni clienta

    template <typename GameType>
    class ServerNetworkSystem : public GengSystem<GameType> {
    public:
        void init(const Fields& client_state_fields);

        virtual FlagsMask getTrackedFlags() override {
            return {};
        }
        virtual RolesMask getNeededRoles() override {
            return {GengEntityRoles::erNetworkedSv};
        }

        virtual void preUpdate() override;
        virtual void updateEntity(Entity& e, float dt);
        virtual void postUpdate() override;

        // this calls deserialize - best for performance to store somewhere for reuse
        template <typename ClientStateType>
        void getClientState(uint32_t client_id, ClientStateType& state_out);
    private:
        struct ClientCtx_ {
            SharedBuffer state_buffer;
            EntitiesSnapshots entities;
        };

        Message encodeDeltaEntity_(PackedEntityState& old_ss, PackedEntityState& new_ss);
        Message encodeFullEntity_(PackedEntityState& ss);

        Server* server_;

        fast_vector<uint32_t> connected_clients_;
        fast_vector<ClientCtx_> client_states_;
        DeltaSerializer delta_serializer_;
        Fields client_state_fields_;
    };

}


#include "ServerNetworkSystem.inl"
#endif //SERVERNETWORKSYSTEM_H
