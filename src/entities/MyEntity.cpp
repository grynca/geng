#include "incl.h"
#include "MyEntity.h"
#include "../MyAssets.h"

// statics
TextureRegion MyEntity::sprite_region;
uint32_t MyEntity::animation_id;


MyEntity::MyEntity() {
}

void MyEntity::initResources(MyGame& game) {
    AssetsManager& am = game.getModule<AssetsManager>();
    sprite_region = *am.getImageRegion("data/sprites/yoda.jpg");
    Animation& anim = am.getAnimations().addItem();
    animation_id = anim.getId();
    anim.init({
                      {"data/sprites/eye1.png", 0.2f},
                      {"data/sprites/eye2.png", 0.2f},
                      {"data/sprites/eye3.png", 0.2f},
                      {"data/sprites/eye4.png", 0.2f},
                      {"data/sprites/eye5.png", 0.2f}
              });
}

GameEntity& MyEntity::create(MyGame& game) {
    GameEntity& ent = game.getSysEnt().getEntityManager().addItem();
    ent.setRoles({EntityRoles::erRenderable, EntityRoles::erMovable});
    MyEntity& me = ent.set<MyEntity>();
    me.getSpeed().setAngularSpeed(Angle::Pi/4);

    RectRenderable & rr = me.getRenderables().add<RectRenderable>().init(game, 0, Vec2{1000, 200});
    float r = (float)rand()/RAND_MAX;
    float g = (float)rand()/RAND_MAX;
    float b = (float)rand()/RAND_MAX;
    rr.setColor(1, 0, 0);

    for (uint32_t i=0; i<3; ++i) {
        int r_to = rand()%100 + 20;
        int r_from = rand()%(r_to-10);
        int x = rand()%1024 - 512;
        int y = rand()%768 - 384;
        CircleRenderable & cc = me.getRenderables().add<CircleRenderable>().init(game, 1, r_to, r_from);
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
        cc.setColor(r, g, b, 1);

        cc.getLocalTransform().setPosition({(float)x, (float)y});
    }

    ImageRenderable& ir = me.getRenderables().add<ImageRenderable>().init(game, 2, 0, sprite_region.getTextureRect(), Vec2{100, 100});

    SpriteRenderable& sr = me.getRenderables().add<SpriteRenderable>().init(game, 2, 0, animation_id);
    sr.setAutoChangeDir(true);
    sr.getLocalTransform().setPosition({-100, 0});

    TextRenderable& tr = me.getRenderables().add<TextRenderable>().init(game, 5, 1, 0, 45, "This is SPARTA!");
    tr.getLocalTransform().setPosition({100, 0});

    return ent;
}

void MyEntity::update() {
    float delta_angle = Angle::Pi*1./360;
    RectRenderable& rr = *((RectRenderable*)getRenderables().get(0));
    rr.setSize(rr.getSize()-Vec2(1, 0));
    rr.setOffset(rr.getOffset()+Vec2(0.5, 0));
    getTransform().setRotation(getTransform().getRotation()+delta_angle);
}