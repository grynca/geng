#ifndef SHUTTLE_H
#define SHUTTLE_H

class Shuttle : public EBodyTree {
public:
    DEF_CONSTR_AND_MOVE_ONLY(Shuttle);

    class Resources : public EntityResources<Resources> {
    public:
        void initSingleton(GameBase& game);

        ImagePos shuttle_img;
        ImagePos particle_img;
        SpriteBodyPars shuttle_params;
    };

    void init();
    void update();
private:

};

#include "Shuttle.inl"
#endif //SHUTTLE_H
