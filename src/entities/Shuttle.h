#ifndef SHUTTLE_H
#define SHUTTLE_H

class Shuttle : public EMovable, public ERenderables {
public:
    Shuttle();

    static void initResources(MyGame& game);
    static GameEntity& create(MyGame& game);

    void update(MyGame& game);
private:
    static TextureRegion sprite_region;
};

#endif //SHUTTLE_H
