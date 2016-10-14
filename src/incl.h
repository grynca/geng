#ifndef ENTS_H
#define ENTS_H

#include "geng.h"
using namespace grynca;

DEFINE_ENUM_E(EntityRoles, GengEntityRoles,
            erDummy, erDummy2
);

class MyGame;
class MyEntity;
class Shuttle;
class HUD;

typedef grynca::TypesPack<MyEntity, Shuttle, HUD> EntityTypes;

#define GET_ETYPE_ID(Type) EntityTypes::pos<Type>()

#include "MyGame.h"
#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"

#endif //ENTS_H
