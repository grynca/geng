#ifndef CNETWORKEDCLIENT_H
#define CNETWORKEDCLIENT_H

#include "CNetworkedServer.h"

namespace grynca {

    class CNetworkedClientData : public CNetworkedServerData {
    public:
        static RolesMask componentRoles() {
            return GERoles::erNetworkedClMask();
        }

        fast_vector<Message> update_messages;
    };

}

#endif //CNETWORKEDCLIENT_H
