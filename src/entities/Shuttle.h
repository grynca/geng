#ifndef SHUTTLE_H
#define SHUTTLE_H

#include "geng.h"
using namespace grynca;

class Shuttle {
public:
    Shuttle();

    static void initResources(Game& game);
    static Entity& create(Game& game);

    void update(Game& game);

    Transform transform;
    Renderables renderables;
    Speed speed;
private:
};

#endif //SHUTTLE_H
