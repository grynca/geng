#ifndef ENTS_H
#define ENTS_H

#include "geng_enums.h"
using namespace grynca;

DEFINE_ENUM_E(MyRoles, GERoles,
              erDummy, erDummy2
);

DEFINE_ENUM(MyCollGroups,
              cgDefaultBody,
              cgDudeLimb
);

#define SYSENT_MAX_ROLES MyRoles::end
#define SYSENT_MAX_FLAGS GEFlags::end
#define GPHYX_MAX_CGROUPS MyCollGroups::end
#include "geng.h"

#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"
#include "entities/Dude.h"

typedef grynca::TypesPack<
        Shuttle, HUD, Dude
> EntityTypes;

#include "MyGame.h"

#endif //ENTS_H
