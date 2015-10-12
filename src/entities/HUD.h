#ifndef HUD_H
#define HUD_H


class HUD : public ENonMovable,
            public ERenderables {
public:
    static GameEntity& create(MyGame& game);

    void update(MyGame& game);
private:
};

#endif //HUD_H
