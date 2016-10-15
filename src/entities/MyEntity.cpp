#include "../incl.h"
#include "MyEntity.h"

// statics
TextureRegion MyEntity::sprite_region;
Index MyEntity::animation_id;

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

Entity MyEntity::create(MyGame& game) {
    Entity ent = game.createEntity(GET_ETYPE_ID(MyEntity));
    ent.getComponent<CMovable>().getSpeed().setAngularSpeed(Angle::Pi/4);

    CRenderables& rs = ent.getComponent<CRenderables>();
    RectRenderable& rr = rs.addRenderable<RectRenderable>().init(game);
    rr.setSize(Vec2{1000, 200});
    rr.setGeomNormOffset(-Vec2{0.5, 0.5});
    rr.setLayerId(0);
    rr.setColor(Colorf::Red());

    RectBorderRenderable& rbr = rs.addRenderable<RectBorderRenderable>().init(game);
    rbr.setSize(Vec2{120, 200});
    rbr.setGeomNormOffset(-Vec2{0.5, 0.5});
    rbr.setLayerId(0);
    rbr.setColor(Colorf::Red());
    rbr.setBorders({50, 20});
    rbr.accLocalTransform().setPosition({(float)250, (float)250});

    for (uint32_t i=0; i<3; ++i) {
        int r_to = rand()%100 + 20;
        int r_from = rand()%(r_to-10);
        int x = rand()%1024 - 512;
        int y = rand()%768 - 384;
        CircleRenderable& cc = rs.addRenderable<CircleRenderable>().init(game, r_to, r_from);
        cc.setLayerId(1);
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
        cc.setColor(Colorf(r, g, b, 1));

        cc.accLocalTransform().setPosition({(float)x, (float)y});
    }

    SpriteRenderable& s1 = rs.addRenderable<SpriteRenderable>().init(game);
    s1.setImageRegion(sprite_region);
    s1.accLocalTransform().setScale(Vec2{0.5, 0.5});
    s1.setTextureUnit(0);
    s1.setLayerId(2);

    SpriteRenderable& s2 = rs.addRenderable<SpriteRenderable>().init(game);
    s2.setTextureUnit(0);
    s2.setAnimation(animation_id);
    s2.setLayerId(2);
    s2.setEndAction(SpriteRenderable::eaChangeDir);
    s2.accLocalTransform().setPosition({-100, 0});

    TextRenderable& tr = rs.addRenderable<TextRenderable>().init(game);
    tr.setTextureUnit(1);
    tr.getTextSetter().setFont(game.assets.fonts_pack_id).setFontSize(45).setText("This is SPARTA!");
    tr.accLocalTransform().setPosition({100, 0});

    PgonRenderable& pr = rs.addRenderable<PgonRenderable>().init(game);
    Vec2 vertices[6] = {
            {268, 162}, {309, 107}, {471, 130}, {517, 257}, {445, 324}, {263, 315}
    };
    ARect bound(vertices, 6);
    for (uint32_t i=0; i<6; ++i) {
        vertices[i] -= bound.getCenter();
        pr.getGeom().addVertex(vertices[i]);
    }
    pr.setLayerId(3);
    pr.accLocalTransform().setPosition({-200, 200});
    pr.accLocalTransform().setScale({0.8f, 0.8f});

    return ent;
}

void MyEntity::update(Entity& e) {
    float delta_angle = Angle::Pi*1./360;
    RectRenderable& rr = e.getComponent<CRenderables>().accRenderables()[0].get<RectRenderable>();
    rr.setSize(rr.getSize()-Vec2(1, 0));

    CTransform& t = e.getComponent<CTransform>();
    t.setRotation(t.get().getRotation() + delta_angle, e);
}