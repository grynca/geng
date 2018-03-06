#ifndef HUD_H
#define HUD_H


class HUD : public EVisual {
public:
    DEF_CONSTR_AND_MOVE_ONLY(HUD);

    class Resources : public EntityResources<Resources> {
    public:
        void initSingleton(GameBase& game);

        ImagePos particle_img;
    };

    void init();
    void update();
private:
};

#include "HUD.inl"
#endif //HUD_H
