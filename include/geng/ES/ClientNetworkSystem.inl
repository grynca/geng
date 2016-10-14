#include "ClientNetworkSystem.h"
#include <vector>
#include "ggnet.h"

#define CNS_TPL template <typename GameType>
#define CNS_TYPE ClientNetworkSystem<GameType>

namespace grynca {

    CNS_TPL
    template <typename ClientStateBase>
    inline void CNS_TYPE::init() {
        client_ = &this->getGame().template getModule<Client>();
        ASSERT_M(client_->isInitialized(), "Client must be initialized prior.");

        client_state_ = new ClientStateBase();
        client_state_->getFields(client_state_fields_);

        client_->addMessageHandler(GengNwMsgType::mtEntityFull, [this](Client::RecvCtx& ctx) {
            uint32_t pos = 0;
            uint16_t ent_type = ctx.message.readShort(pos);
            uint32_t ent_index = ctx.message.readInt(pos);
            EntityIndex ent_id(ent_index, ent_type);

            Entity entity;
            typename EntityIdsMap::iterator it = entity_updates_.find(ent_id);
            if (it == entity_updates_.end()) {
                // mapping unknown -> create new entity
                entity = this->getGameBase().createEntity(ent_type);
                it = entity_updates_.emplace().first;
                it->second = entity.getIndex();
            }
            else {
                // full update renders previous update messages obsolete
                entity =  this->getGameBase().getEntity(it->second);
                entity.getComponent<CNetworkedClient>().update_messages.clear();
            }

            entity.getComponent<CNetworkedClient>().update_messages.push_back(ctx.message.clone());
        });

        client_->addMessageHandler(GengNwMsgType::mtEntityDelta, [this](Client::RecvCtx& ctx) {
            uint32_t pos = 0;
            uint16_t ent_type = ctx.message.readShort(pos);
            uint32_t ent_index = ctx.message.readInt(pos);
            EntityIndex ent_id{ent_index, ent_type};

            typename EntityIdsMap::iterator it = entity_updates_.find(ent_id);
            if (it == entity_updates_.end()) {
                NEVER_GET_HERE("Delta update for non existing entity - should not happen.");
                return;
            }

            Entity entity =  this->getGameBase().getEntity(it->second);
            entity.getComponent<CNetworkedClient>().update_messages.push_back(ctx.message.clone());
        });
    }

    CNS_TPL
    inline void CNS_TYPE::preUpdate() {
        /** sending of client state to server **/

        client_state_->update(this->getGame());
        client_state_snapshots_.add();
        ClientStateSnapshot& latest_ss = client_state_snapshots_.getCurrent();

        latest_ss.state.serialize(client_state_, client_state_fields_);

        uint32_t snapshots_count = client_state_snapshots_.getSize();
        ClientStateSnapshot* delta_to = NULL;
        bool has_prev_snapshots = (snapshots_count!=1);
        if (has_prev_snapshots) {
            for (uint32_t j=1; j<snapshots_count; ++j) {
                ClientStateSnapshot& ss = client_state_snapshots_.getPrev(j);
                if (ss.isAcked(client_->getConnection())) {
                    delta_to = &ss;
                    break;
                }
            }
        }

        if (delta_to) {
            // send client state delta
            client_->addMessage(encodeDeltaClientState_(*delta_to, latest_ss), &latest_ss.seq_id);
        }
        else {
            // send full client state
            client_->addMessage(encodeFullClientState_(latest_ss), &latest_ss.seq_id);
        }
    }

    CNS_TPL
    inline void CNS_TYPE::updateEntity(Entity& e, float dt) {
//        CNetworkedClient& nc = e.getComponent<CNetworkedClient>();
//
//        if (nc.update_messages.empty()) {
//            return;
//        }
//
//        Fields fields;
//        nc.getFields(fields);
//
//        // TODO: nejakou interpolaci mezi server -> client stavem
//        //       popripade kdyz je rozdil moc velkej tak natvrdo setnout server stav
//
//        if (nc.update_messages.size() == 1 && nc.update_messages[0].getMessageType()==GengNwMsgType::mtEntityFull) {
//            // deserialize from full update
//            fields.deserializeFull(entity.getData(), nc.update_messages[0].getPayload());
//        }
//        else {
//            // deserialize from delta_update(s)
//            uint32_t mask_size = fields.getMaskSize();
//            std::vector<bool>field_loaded(fields.getFieldsCount());
//            for (int32_t i=nc.update_messages.size()-1; i>=0; --i) {
//                uint8_t* src = const_cast<uint8_t*>(nc.update_messages[i].getPayload());
//                DeltaMask mask(src, mask_size);
//                src += mask_size;
//                for (uint32_t fid=0; fid<mask_size; ++fid) {
//                    uint32_t field_size = fields.getFieldSize(fid);
//                    if (!field_loaded[fid] && mask.get(fid)) {
//                        fields.deserializeField(entity.getData(), src, fid);
//                        field_loaded[fid] = true;
//                    }
//                    src += field_size;
//                }
//            }
//        }
//        nc.update_messages.clear();
    }

    CNS_TPL
    inline void CNS_TYPE::postUpdate() {
    }

    CNS_TPL
    Message CNS_TYPE::encodeDeltaClientState_(ClientStateSnapshot& old_ss, ClientStateSnapshot& new_ss) {
        assert(old_ss.state.getFields().getFieldsCount() == new_ss.state.getFields().getFieldsCount());

        delta_serializer_.calcDelta(new_ss.state, old_ss.state);
        uint32_t message_size =  delta_serializer_.getNeededSize();
        Message msg(false, GengNwMsgType::mtClientStateDelta, message_size);
        delta_serializer_.saveToBuf(new_ss.state, msg.getBack());
        msg.setSize(message_size);
        return msg;
    }

    CNS_TPL
    Message CNS_TYPE::encodeFullClientState_(ClientStateSnapshot& ss) {

        uint32_t message_size = ss.state.getBuffer().getSize();
        Message msg(false, GengNwMsgType::mtClientStateFull, message_size);
        msg.pushBack(ss.state.getBuffer().getData(), ss.state.getBuffer().getSize());
        return msg;
    }

}

#undef CNS_TPL
#undef CNS_TYPE
#undef ENTITY_TYPE