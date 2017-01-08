#ifndef HUD_H
#define HUD_H


class HUD : public GengEntityDef<CTransform, CRenderables> {
public:
    class Resources : public Singleton<Resources> {
    public:
        Resources(GameBase& game);

        TextureRegion particle_region;
    };

    static void init(Entity& ent, GameBase& game);
    static void update(Entity& e, GameBase& game);
private:
};

#include "HUD.inl"
#endif //HUD_H
