#ifndef ENTS_H
#define ENTS_H

#include "geng.h"
using namespace grynca;


class MyGame;
class MyEntity;
class Shuttle;
class HUD;

typedef grynca::TypesPack<MyEntity, Shuttle, HUD> EntityTypes;
typedef grynca::TypesPack<grynca::MovementSystem> UpdateSystemTypes;
typedef grynca::TypesPack<grynca::RenderSystem> RenderystemTypes;

DEFINE_ENUM_E(EntityRoles, GengEntityRoles,
            erDummy, erDummy2
);

typedef grynca::Entity<EntityTypes> GameEntity;

#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"

#include "MyGame.h"

#endif //ENTS_H
