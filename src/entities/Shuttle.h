#ifndef SHUTTLE_H
#define SHUTTLE_H

class Shuttle : public GengEntityDef<CMovable, CTransform, CRenderables, CBody> {
public:
    static void initResources(MyGame& game);
    static Entity create(MyGame& game);

    static void update(Entity& e, MyGame& game);
private:
    static TextureRegion sprite_region;
};

#endif //SHUTTLE_H
