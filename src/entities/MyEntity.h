#ifndef MYENTITY_H
#define MYENTITY_H

#include "geng.h"
using namespace grynca;

class MyEntity {
public:
    MyEntity();

    static void initResources(Game& game);
    static Entity& create(Game& game);

    void update();
    Transform transform;
    Renderables renderables;
    Speed speed;
private:
};

#endif //MYENTITY_H
