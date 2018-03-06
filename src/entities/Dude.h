#ifndef GENG_DUDE_H
#define GENG_DUDE_H

class Dude : public EBody {
public:
    DEF_CONSTR_AND_MOVE_ONLY(Dude);

    class Resources : public EntityResources<Resources> {
    public:
        enum LimbType {
            ltLarm,
            ltRarm,
            ltLleg,
            ltRleg,

            ltCount
        };

        void initSingleton(GameBase &game);

        struct : CircleBodyPars {
            Vec2 position;
        } head_params;

        struct : RectBodyPars1 {
            Vec2 position;
            f32 rotation;
        } limb_params[ltCount];

        RectBodyPars1 chest_params;
    };

    void init(const Vec2& pos);
    void update();
    void onKilled();
};

#include "Dude.inl"

#endif //GENG_DUDE_H