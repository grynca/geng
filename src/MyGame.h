#ifndef MYGAME_H
#define MYGAME_H

#include "incl.h"

class MyGame : public grynca::Game<MyEntSys, MyGame> {
public:

private:
    GameEntity::IndexType test_ent_id;
    GameEntity::IndexType shuttle_id;
    GameEntity::IndexType hud_id;

    virtual void init() override;
    virtual void update() override;
    virtual void tick() override;
};



#endif //MYGAME_H
