#include "sysent.h"
#include "MyEntity.h"


MyEntity::MyEntity() {
}

void MyEntity::initResources(Game& game) {
    Texture2D& t = game.getModule<Window>().getTextures().addItem("yoda");
    t.bind(0);
    t.set(RefPtr<Image>(new Image("data/yoda.jpg")));
}

Entity& MyEntity::create(Game& game) {
    Entity& ent = game.getModule<EntityManager>().addItem();
    ent.setRoles({erRenderable, erMovable});
    MyEntity& me = ent.set<MyEntity>();
    me.speed.setAngularSpeed(Angle::Pi/4);

    RectRenderable & rr = me.renderables.add<RectRenderable>(game.getModule<Window>(), 0, Vec2{1000, 200});
    float r = (float)rand()/RAND_MAX;
    float g = (float)rand()/RAND_MAX;
    float b = (float)rand()/RAND_MAX;
    rr.setColor(1, 0, 0);

    for (uint32_t i=0; i<3; ++i) {
        int r_to = rand()%100 + 20;
        int r_from = rand()%(r_to-10);
        int x = rand()%1024 - 512;
        int y = rand()%768 - 384;
        CircleRenderable & cc = me.renderables.add<CircleRenderable>(game.getModule<Window>(), 1, r_to, r_from);
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
        cc.setColor(r, g, b, 1);

        cc.getLocalTransform().setPosition({(float)x, (float)y});
    }

    SpriteRenderable & sr = me.renderables.add<SpriteRenderable>(game.getModule<Window>(), 2, 0, Vec2{100, 100});

    return ent;
}

void MyEntity::update() {
    float delta_angle = Angle::Pi*1./180;
    RectRenderable rr = *((RectRenderable*)renderables.get(0));
    rr.setSize(rr.getSize()-Vec2(1, 0));
    rr.setOffset(rr.getOffset()+Vec2(0.5, 0));
    transform.setRotation(transform.getRotation()+delta_angle);
}