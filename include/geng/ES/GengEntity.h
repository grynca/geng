#ifndef GENG_ENTITY_H
#define GENG_ENTITY_H

#include "GengEntityRoles.h"
#include <bitset>

namespace grynca {

    class GengEntity : public EntityBase {
    public:
        enum FlagIds {
            fMoved,
            fRotated,
            fScaled,
        // ==========
            flagsCount
        };

        std::bitset<flagsCount>& getFlags() { return flags_; }

    private:
        std::bitset<flagsCount> flags_;
    };

}

#endif //GENG_ENTITY_H
