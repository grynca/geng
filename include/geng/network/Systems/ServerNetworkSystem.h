#ifndef SERVERNETWORKSYSTEM_H
#define SERVERNETWORKSYSTEM_H

#include "geng/core/GengSystem.h"
#include "geng/network/Components/CNetworkedServer.h"
#include "types/containers/SharedBuffer.h"
#include "../Snapshots.h"

namespace grynca {

    // fw
    class Server;

    // TODO:
    //  prepsat z post/pre update do novyho update stylu
    //  pridat do Server classy registraci callbacku na pripojeni a odpojeni clientu
    //  ActionsStateType bude mit clear() kterej budu volat v hadleru po pripojeni clienta

    class ServerNetworkSystem : public GengSystemAll {
    public:
        void init(const Fields& client_state_fields);

        virtual RolesMask NeededRoles() override {
            return GERoles::erNetworkedSvMask();
        }

        virtual void update(f32 dt, EntitiesList& entities) override;

        // this calls deserialize - best for performance to store somewhere for reuse
        template <typename ClientStateType>
        void getClientState(u32 client_id, ClientStateType& state_out);
    private:
        struct ClientCtx_ {
            SharedBuffer state_buffer;
            EntitiesSnapshots entities;
        };

        Message encodeDeltaEntity_(PackedEntityState& old_ss, PackedEntityState& new_ss);
        Message encodeFullEntity_(PackedEntityState& ss);

        Server* server_;

        fast_vector<u32> connected_clients_;
        fast_vector<ClientCtx_> client_states_;
        DeltaSerializer delta_serializer_;
        Fields client_state_fields_;
    };

}


#include "ServerNetworkSystem.inl"
#endif //SERVERNETWORKSYSTEM_H
