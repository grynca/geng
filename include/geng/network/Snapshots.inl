#include "Snapshots.h"
#include "geng/network/Components/CNetworkedServer.h"

namespace grynca {

    template <typename EntityType>
    inline void PackedEntityState::serialize(const EntityType& entity)
    {
        Fields fields;
        entity.template getData<CNetworkedServerData>().getFields(fields);
        SerializedBuffer::serialize(entity.getData(), fields);
    }

    inline EntityIndex PackedEntityState::getEntityId()const {
        return ent_id_;
    }

    inline EntitiesSnapshot::EntitiesSnapshot()
    {}

    inline bool EntitiesSnapshot::isAcked(const Connection& conn) {
        for (u32 i=0; i<seq_ids.size(); ++i) {
            if (conn.getPacketAckState(seq_ids[i]) != Network::sAcked)
                return false;
        }
        return true;
    }

    inline bool ClientStateSnapshot::isAcked(const Connection& conn) {
        return conn.getPacketAckState(seq_id) != Network::sAcked;
    }

    inline PackedEntityState* EntitiesSnapshot::findEntityState(EntityIndex ent_id) {
        for (u32 i=0; i<ent_states.size(); ++i) {
            if (ent_states[i].getEntityId() == ent_id)
                return &ent_states[i];
        }
        return NULL;
    }
}