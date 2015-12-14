#ifndef ENTS_H
#define ENTS_H

#include "geng.h"
using namespace grynca;


class MyGame;
class MyEntity;
class Shuttle;
class HUD;

typedef grynca::TypesPack<MyEntity, Shuttle, HUD> EntityTypes;
typedef grynca::TypesPack<
        grynca::StartTickSystem<MyGame>,
        grynca::MovementSystem<MyGame>,
        grynca::CollisionSystem<MyGame>
> UpdateSystemTypes;
typedef grynca::TypesPack<
        grynca::RenderSystem<MyGame>
> RenderystemTypes;

DEFINE_ENUM_E(EntityRoles, GengEntityRoles,
            erDummy, erDummy2
);

typedef grynca::Entity<EntityTypes> GameEntity;

typedef grynca::ES<EntityTypes, UpdateSystemTypes, RenderystemTypes, EntityRoles> MyEntSys;

#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"

#include "MyGame.h"

#endif //ENTS_H
