#ifndef CNETWORKED_H
#define CNETWORKED_H

#include "GengEntityRoles.h"
#include "GengEntity.h"

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
            return {GengEntityRoles::erNetworkedSv};
        }

        virtual void getFields(Fields& fields_out)const {
            NEVER_GET_HERE("Override this method for your networked entity types.");
            return;
        }
    };

    class CNetworkedClient : public CNetworked {
    public:
        static RolesMask componentRoles() {
            return {GengEntityRoles::erNetworkedCl};
        }

        fast_vector<Message> update_messages;
    };

}

#endif //CNETWORKED_H
