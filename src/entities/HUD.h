#ifndef HUD_H
#define HUD_H


class HUD  : public GengEntityDef<CTransform, CRenderables> {
public:
    static Entity create(MyGame& game);

    static void update(Entity& e, MyGame& game);
private:
};

#endif //HUD_H
