#include "../incl.h"
#include "MyEntity.h"

//inline void MyEntity::Resources::init(GameBase& game) {
//    AssetsManager& am = game.getModule<Window>().getAssets();
//    animation = am.getSpriteAnimations().addItem();
//    animation->setFrames({
//                      {"data/sprites/eye1.png", 0.2f},
//                      {"data/sprites/eye2.png", 0.2f},
//                      {"data/sprites/eye3.png", 0.2f},
//                      {"data/sprites/eye4.png", 0.2f},
//                      {"data/sprites/eye5.png", 0.2f}
//              });
//}
//
//inline void MyEntity::init() {
//    //static Resources &res = Resources::get();
//
////    CTransform tr = getAndInit<CTransform>(partsCount);
////    CRenderable rs = getAndInit<CRenderable>(partsCount);
////
////    tr.accPart(pAnimSprite).setPosition({50, 150});
////    auto anim_sprite = rs.setPartRenderable<SpriteRenderable>(pAnimSprite, cfScreenGlobal);
////    anim_sprite.setNewGeom(NormOffset::getTransform(NormOffset::otCenter));
////    anim_sprite.setTextureUnit(0);
////    anim_sprite.setAnimated(true);
////    anim_sprite.accRenderTask().setLayer(10);
////    anim_sprite.accAnimationState()
////            .setAnimation(res.animation)
////            .setEndAction(GeomStateSpriteAnimation::eaChangeDir);
////
////
////    Vec2 vertices[6] = {
////            {268, 162}, {309, 107}, {471, 130}, {517, 257}, {445, 324}, {263, 315}
////    };
////    ARect bound(vertices, 6);
////    auto poly_r = rs.setPartRenderable<PgonRenderable>(pPolygon, cfScreenGlobal);
////    poly_r.setNewGeom();
////    for (u32 i=0; i<6; ++i) {
////        vertices[i] -= bound.getCenter();
////        poly_r.accRenderTask().accGeom()->addVertex(vertices[i]);
////    }
////    poly_r.setColor(Colorf::White());
////    poly_r.accRenderTask().setLayer(10);
////    tr.accPart(pPolygon)
////        .setPosition({50, 250})
////        .setScale({0.3f, 0.3f});
////
////
////
////    tr.accPart(pCircle).setPosition({50, 350});
////    auto circle_r = rs.setPartRenderable<CircleRenderable>(pCircle, cfScreenGlobal);
////    circle_r.setGeomInternal();
////    circle_r.accRenderTask().setLayer(10);
////    circle_r.setColor(Colorf::Blue());
////    circle_r.setInnerRadius(20);
////    circle_r.setOuterRadius(40);
//}
//
//inline void MyEntity::update() {
//
//}