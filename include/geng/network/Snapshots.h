#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include "ggnet/SerializedBuffer.h"
#include "ggnet/Connection.h"
#include "types/containers/RoundBuffer.h"
#include "sysent/EntityIndex.h"

namespace grynca {

    class PackedEntityState : public SerializedBuffer {
    public:
        template <typename EntityType>
        void serialize(const EntityType& entity);
        EntityIndex getEntityId()const;
    private:
        EntityIndex ent_id_;
    };

    class EntitiesSnapshot {
    public:
        EntitiesSnapshot();
        PackedEntityState* findEntityState(EntityIndex ent_id);

        bool isAcked(const Connection& conn);

        fast_vector<u16> seq_ids;     // seq ids of packets containing snapshot
        fast_vector<PackedEntityState> ent_states;
    };

    class ClientStateSnapshot {
    public:

        bool isAcked(const Connection& conn);

        u16 seq_id;    // seq id of packet containing snapshot
        SerializedBuffer state;
    };

    typedef RoundBuffer<EntitiesSnapshot, 32> EntitiesSnapshots;
    typedef RoundBuffer<ClientStateSnapshot, 32> ClientStateSnapshots;
}

#include "Snapshots.inl"
#endif //SNAPSHOTS_H
