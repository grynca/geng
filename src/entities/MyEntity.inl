#include "../incl.h"
#include "MyEntity.h"

inline MyEntity::Resources::Resources(GameBase& game) {
    AssetsManager& am = game.getModule<AssetsManager>();
    SpriteAnimation& anim = am.getSpriteAnimations().addItem();
    animation_id = anim.getId();
    anim.setFrames({
                      {"data/sprites/eye1.png", 0.2f},
                      {"data/sprites/eye2.png", 0.2f},
                      {"data/sprites/eye3.png", 0.2f},
                      {"data/sprites/eye4.png", 0.2f},
                      {"data/sprites/eye5.png", 0.2f}
              });
}

inline void MyEntity::init(Entity& ent, GameBase& game) {
    CRenderables& rs = ent.getComponent<CRenderables>();

    SpriteRenderable eye_r = rs.addRenderable<SpriteRenderable>();
    eye_r.accRenderTask()->setLayer(10);
    eye_r.accRenderTask()->setCoordFrame(cfScreenGlobal);
    eye_r.setPosition({50, 150});
    eye_r.setTextureUnit(0);
    eye_r.setAnimated(true);
    eye_r.accAnimationState().setAnimationId(Resources::get().animation_id)
                             .setEndAction(SpriteAnimationState::eaChangeDir);

    PgonRenderable poly_r = rs.addRenderable<PgonRenderable>();
    Vec2 vertices[6] = {
            {268, 162}, {309, 107}, {471, 130}, {517, 257}, {445, 324}, {263, 315}
    };
    ARect bound(vertices, 6);
    for (u32 i=0; i<6; ++i) {
        vertices[i] -= bound.getCenter();
        poly_r.accRenderTask()->accGeom()->addVertex(vertices[i]);
    }
    poly_r.accRenderTask()->setLayer(10);
    poly_r.accRenderTask()->setCoordFrame(cfScreenGlobal);
    poly_r.accRenderTask()->accLocalTransform().setScale({0.3f, 0.3f});
    poly_r.setPosition({50, 250});
    poly_r.setColor(Colorf::White());

    CircleRenderable circle_r = rs.addRenderable<CircleRenderable>();
    circle_r.accRenderTask()->setCoordFrame(cfScreenGlobal);
    circle_r.accRenderTask()->setLayer(10);
    circle_r.setColor(Colorf::Blue());
    circle_r.setInnerRadius(20);
    circle_r.setOuterRadius(40);
    circle_r.setPosition({50, 350});
}

inline void MyEntity::update(Entity& e, GameBase& game) {

}