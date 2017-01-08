#ifndef CNETWORKED_H
#define CNETWORKED_H

#include "geng/GERoles.h"
#include "../../core/GengEntity.h"
#include "ggnet/Message.h"

namespace grynca {

    DEFINE_ENUM(GengNwMsgType,
                mtEntityFull,
                mtEntityDelta,
                mtClientStateFull,
                mtClientStateDelta
    );

    class CNetworked {
    public:
        static RolesMask componentRoles() {
            return GERoles::erNetworkedSvMask();
        }

        virtual void getFields(Fields& fields_out)const {
            NEVER_GET_HERE("Override this method for your networked entity types.");
            return;
        }
    };

    class CNetworkedClient : public CNetworked {
    public:
        static RolesMask componentRoles() {
            return GERoles::erNetworkedClMask();
        }

        fast_vector<Message> update_messages;
    };

}

#endif //CNETWORKED_H
