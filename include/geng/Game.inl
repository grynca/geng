#include "Game.h"
#include "types/Type.h"

namespace grynca {

    template <typename T>
    inline T& Game::getModule() {
        // lazy get
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].getAs<T>())
            modules_[tid] = CommonPtr(new T());

        CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    template <typename T>
    inline bool Game::containsModule_() {
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        CommonPtr& ptr = modules_[tid];
        return ptr.getAs<T>() != NULL;
    }
}