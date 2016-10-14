#ifndef CLIENTSTATEBASE_H
#define CLIENTSTATEBASE_H

#include "ggnet/Fields.h"

namespace grynca {

    template <typename GameType>
    class ClientStateBase {
    public:
        virtual ~ClientStateBase() {}

        virtual void update(GameType& game) = 0;
        virtual void getFields(Fields& f) = 0;
    };

}

#endif //CLIENTSTATEBASE_H
