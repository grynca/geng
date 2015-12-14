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
    MyEntity& me = ent.set<MyEntity>();
    me.getSpeed().setAngularSpeed(Angle::Pi/4);
    
    RectRenderable& rr = me.getRenderables().add<RectRenderable>(game);
    rr.setSize(Vec2{1000, 200});
    rr.setOffset(-Vec2{0.5, 0.5});
    rr.setLayerId(0);
    float r = (float)rand()/RAND_MAX;
    float g = (float)rand()/RAND_MAX;
    float b = (float)rand()/RAND_MAX;
    rr.setColor(1, 0, 0);

    for (uint32_t i=0; i<3; ++i) {
        int r_to = rand()%100 + 20;
        int r_from = rand()%(r_to-10);
        int x = rand()%1024 - 512;
        int y = rand()%768 - 384;
        CircleRenderable& cc = me.getRenderables().add<CircleRenderable>(game, r_to, r_from);
        cc.setLayerId(1);
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
        cc.setColor(r, g, b, 1);

        cc.getLocalTransform().setPosition({(float)x, (float)y});
    }

    SpriteRenderable& s1 = me.getRenderables().add<SpriteRenderable>(game);
    s1.setImageRegion(sprite_region);
    s1.getLocalTransform().setScale(Vec2{0.5, 0.5});
    s1.setTextureUnit(0);
    s1.setLayerId(2);

    SpriteRenderable& s2 = me.getRenderables().add<SpriteRenderable>(game);
    s2.setTextureUnit(0);
    s2.setAnimation(animation_id);
    s2.setLayerId(2);
    s2.setEndAction(SpriteRenderable::eaChangeDir);
    s2.getLocalTransform().setPosition({-100, 0});

    TextRenderable& tr = me.getRenderables().add<TextRenderable>().init(game);
    tr.setTextureUnit(1);
    tr.getTextSetter().setFont(0).setFontSize(45).setText("This is SPARTA!");
    tr.getLocalTransform().setPosition({100, 0});

    return ent;
}

void MyEntity::update() {
    float delta_angle = Angle::Pi*1./360;
    RectRenderable& rr = *((RectRenderable*)getRenderables().get(0));
    rr.setSize(rr.getSize()-Vec2(1, 0));
    setRotation(getTransform().getRotation()+delta_angle);
}