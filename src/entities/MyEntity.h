#ifndef MYENTITY_H
#define MYENTITY_H

class MyEntity : public EMovable, public ERenderables {
public:
    MyEntity();

    static void initResources(MyGame& game);
    static GameEntity& create(MyGame& game);

    void update();
private:
    static TextureRegion sprite_region;
    static uint32_t animation_id;
};

#endif //MYENTITY_H
