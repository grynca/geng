#ifndef MYGAME_H
#define MYGAME_H

#include "incl.h"

class MyGame : public grynca::Game<EntityTypes, UpdateSystemTypes, RenderystemTypes, EntityRoles>,
               public grynca::Singleton<MyGame> {
public:

private:
    GameEntity* test_ent;
    GameEntity* shuttle;
    GameEntity* hud;

    virtual void init() override;
    virtual void update() override;
    virtual void tick() override;
};



#endif //MYGAME_H
