#include <ggnet/DeltaSerializer.h>
#include "ServerNetworkSystem.h"
#include "ggnet.h"

namespace grynca {

//    SNS_TPL
//    inline void SNS_TYPE::init(const Fields& client_state_fields) {
//        client_state_fields_ = client_state_fields;
//        server_ = &this->getGame().template getModule<Server>();
//        ASSERT_M(server_->isInitialized(), "Server must be initialized prior.");
//        client_states_.resize(server_->getSlotsCount());
//
//        server_->addMessageHandler(GengNwMsgType::mtClientStateFullId, [this](Server::RecvCtx& ctx) {
//            this->client_states_[ctx.slot_id].state_buffer.clear();
//            this->client_states_[ctx.slot_id].state_buffer.pushBack(ctx.message.getPayload(), ctx.message.getPayloadSize());
//        });
//
//        server_->addMessageHandler(GengNwMsgType::mtClientStateDeltaId, [this](Server::RecvCtx& ctx) {
//            u8* src = const_cast<u8*>(ctx.message.getPayload());
//            // get mask from message
//            u32 mask_size = client_state_fields_.getMaskSize();
//            DeltaMask mask(src, mask_size);
//            src += mask_size;
//
//            u8* dst = client_states_[ctx.slot_id].state_buffer.getData();
//
//            // store updated fields to stored serialized client state
//            for (u32 i=0; i<client_state_fields_.getFieldsCount(); ++i) {
//                u32 field_size = client_state_fields_.getFieldSize(i);
//                if (mask.get(i)) {
//                    memcpy(dst, src, field_size);
//                    src += field_size;
//                }
//                dst += field_size;
//            }
//        });
//    }
//
//    SNS_TPL
//    inline void SNS_TYPE::preUpdate(f32 dt) {
//
//        connected_clients_.clear();
//        for (u32 i=0; i<server_->getSlotsCount(); ++i) {
//            Server::Slot& slot = server_->getSlot(i);
//            if (slot.isConnected()) {
//                connected_clients_.push_back(i);
//                client_states_[i].entities.add();
//                client_states_[i].entities.getCurrent().seq_ids.clear();
//                client_states_[i].entities.getCurrent().ent_states.clear();
//            }
//            else {
//                client_states_[i].entities.clear();
//            }
//        }
//    }
//
//    // TODO:
//    inline bool isVisibleOnClient(EntityIndex ent_id, u32 client_id) {
//        return true;
//    }
//
//    SNS_TPL
//    inline void SNS_TYPE::updateEntity(Entity& e, f32 dt) {
//        EntityIndex ent_id =  e.getIndex();
//
//        bool visibleOnSomeClient = false;
//        for (u32 i=0; i<connected_clients_.size(); ++i) {
//            u32 client_id = connected_clients_[i];
//            if (isVisibleOnClient(ent_id, client_id)) {
//                visibleOnSomeClient = true;
//                break;
//            }
//        }
//
////        if (!visibleOnSomeClient)
////            return;
//
//        for (u32 i=0; i<connected_clients_.size(); ++i) {
//            u32 client_id = connected_clients_[i];
//            if (isVisibleOnClient(ent_id, client_id)) {
//                client_states_[client_id].entities.getCurrent().ent_states.emplace_back();
//                client_states_[client_id].entities.getCurrent().ent_states.back().serialize(e);
//            }
//        }
//    }
//
//    SNS_TPL
//    inline void SNS_TYPE::postUpdate(f32 dt) {
//        for (u32 i=0; i<connected_clients_.size(); ++i) {
//            u32 client_id = connected_clients_[i];
//            u32 snapshots_count = client_states_[client_id].entities.getSize();
//
//            EntitiesSnapshot* delta_to = NULL;
//            bool has_prev_snapshots = (snapshots_count!=1);
//            if (has_prev_snapshots) {
//                for (u32 j=1; j<snapshots_count; ++j) {
//                    EntitiesSnapshot& ss = client_states_[client_id].entities.getPrev(j);
//                    if (ss.isAcked(server_->getSlot(client_id).getConnection())) {
//                        delta_to = &ss;
//                        break;
//                    }
//                }
//            }
//
//            EntitiesSnapshot& latest_ss = client_states_[client_id].entities.getCurrent();
//
//            if (delta_to) {
//                // send entity delta update
//                for (int j=0; j<latest_ss.ent_states.size(); ++j) {
//                    PackedEntityState& curr_ent_state = latest_ss.ent_states[j];
//                    PackedEntityState* prev_ent_state = delta_to->findEntityState(curr_ent_state.getEntityId());
//                    u16 pck_seq_id;
//                    if (prev_ent_state)
//                        server_->addMessage(client_id, encodeDeltaEntity_(*prev_ent_state, curr_ent_state), &pck_seq_id);
//                    else
//                        server_->addMessage(client_id, encodeFullEntity_(curr_ent_state), &pck_seq_id);
//                    if (latest_ss.seq_ids.empty() || latest_ss.seq_ids.back()!=pck_seq_id) {
//                        latest_ss.seq_ids.push_back(pck_seq_id);
//                    }
//                }
//            }
//            else {
//                // send full entity update
//                for (int j=0; j<latest_ss.ent_states.size(); ++j) {
//                    PackedEntityState& curr_ent_state = latest_ss.ent_states[j];
//                    u16 pck_seq_id;
//                    server_->addMessage(client_id, encodeFullEntity_(curr_ent_state), &pck_seq_id);
//                    if (latest_ss.seq_ids.empty() || latest_ss.seq_ids.back()!=pck_seq_id) {
//                        latest_ss.seq_ids.push_back(pck_seq_id);
//                    }
//                }
//            }
//        }
//    }
//
//    SNS_TPL
//    template <typename ClientStateType>
//    inline void SNS_TYPE::getClientState(u32 client_id, ClientStateType& state_out) {
//        client_state_fields_.deserializeFull(&state_out, client_states_[client_id].state_buffer.getData());
//    }
//
//    SNS_TPL
//    inline Message SNS_TYPE::encodeDeltaEntity_(PackedEntityState& old_ss, PackedEntityState& new_ss) {
//        assert(old_ss.getFields().getFieldsCount() == new_ss.getFields().getFieldsCount());
//
//        EntityIndex ent_id = new_ss.getEntityId();
//
//        delta_serializer_.calcDelta(new_ss, old_ss);
//
//        u32 message_size = 2 /*ent type id*/ + 4 /*entity id*/ + delta_serializer_.getNeededSize();
//        Message msg(false, GengNwMsgType::mtEntityDeltaId, message_size);
//        msg.writeShort(ent_id.getEntityTypeId());
//        msg.writeInt(ent_id.getEntityIndex());
//
//        delta_serializer_.saveToBuf(new_ss, msg.getBack());
//        msg.setSize(message_size);
//        return msg;
//    }
//
//    SNS_TPL
//    inline Message SNS_TYPE::encodeFullEntity_(PackedEntityState& ss) {
//        EntityIndex ent_id = ss.getEntityId();
//
//        u32 message_size = 2 /*ent type id*/ + 4 /*entity id*/ + ss.getBuffer().getSize();
//        Message msg(false, GengNwMsgType::mtEntityDeltaId, message_size);
//        msg.writeShort(ent_id.getEntityTypeId());
//        msg.writeInt(ent_id.getEntityIndex());
//        msg.pushBack(ss.getBuffer().getData(), ss.getBuffer().getSize());
//        return msg;
//    }
}