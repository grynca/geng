#ifndef CLIENTSTATEBASE_H
#define CLIENTSTATEBASE_H

#include "ggnet/Fields.h"
#include "../GameBase.h"

namespace grynca {

    class ClientStateBase {
    public:
        virtual ~ClientStateBase() {}

        virtual void update(GameBase& game) = 0;
        virtual void getFields(Fields& f) = 0;
    };

}

#endif //CLIENTSTATEBASE_H
