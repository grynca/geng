#ifndef SHUTTLE_H
#define SHUTTLE_H

class Shuttle : public GengEntityDef<CMovable, CTransform, CRenderables, CBody> {
public:
    class Resources : public Singleton<Resources> {
    public:
        Resources(GameBase& game);

        TextureRegion sprite_region;
        TextureRegion particle_region;
    };

    static void init(Entity& e, GameBase& game);
    static void update(Entity& e, GameBase& game);
private:

};

#include "Shuttle.inl"
#endif //SHUTTLE_H
