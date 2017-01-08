#ifndef ENTS_H
#define ENTS_H

#include "geng_enums.h"
using namespace grynca;

DEFINE_ENUM_E(MyRoles, GERoles,
              erDummy, erDummy2
);

#define SYSENT_MAX_ROLES MyRoles::end
#define SYSENT_MAX_FLAGS GEFlags::end
#include "geng.h"

class MyGame;
class MyEntity;
class Shuttle;
class HUD;

typedef grynca::TypesPack<
        grynca::GUIElement,
        MyEntity, Shuttle, HUD
> EntityTypes;

#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"
#include "MyGame.h"

#endif //ENTS_H
