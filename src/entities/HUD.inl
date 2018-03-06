#include "../incl.h"
#include "HUD.h"

inline void HUD::Resources::initSingleton(GameBase& game) {
    particle_img = game.getModule<Window>().getAssets().findImagePos("data/sprites/particle_rp.png");
}

inline void HUD::init() {
//    static Resources &res = Resources::get();

//    auto tr = getAndInit<CTransform>(partsCount);
//    auto rs = getAndInit<CRenderable>(partsCount);

//    TextRenderable fps = rs.addRenderable<TextRenderable>();
//    fps.accRenderTaskPtr()->setLayer(10);
//    fps.accRenderTaskPtr()->setCoordFrame(cfScreenGlobal);
//    fps.setColor(Colorf::White());
//    fps.setTextureUnit(1);
//    fps.accTextState().setFont("arial", 30).setText("FPS: ");
//    fps.setPosition({10, 40});
//
//    TextRenderable ups = rs.addRenderable<TextRenderable>();
//    ups.accRenderTaskPtr()->setLayer(10);
//    ups.accRenderTaskPtr()->setCoordFrame(cfScreenGlobal);
//    ups.setColor(Colorf::White());
//    ups.setTextureUnit(1);
//    ups.accTextState().setFont("arial", 30).setText("UPS: ");
//    ups.setPosition({10, 90});
//
//    TextRenderable particles_label = rs.addRenderable<TextRenderable>();
//    particles_label.accRenderTaskPtr()->setLayer(10);
//    particles_label.accRenderTaskPtr()->setCoordFrame(cfScreenGlobal);
//    particles_label.setColor(Colorf::White());
//    particles_label.setTextureUnit(1);
//    particles_label.accTextState().setFont("arial", 30).setText("Particles: ");
//    particles_label.setPosition({500, 40});

//    auto ps = rs.setPartRenderable<ParticlesRenderable>(pStars, cfScreenGlobal);
//    ps.setNewGeom();
//    ps.accRenderTask().setLayer(1);
//    ps.accParticlesState().setGravityDir({0, 1.0f}).setMaxTime(30);
//    ps.setParticlesSize({20, 30});
//    ps.setImage(res.particle_img);
}

inline void HUD::update() {
    CRenderable rs = get<CRenderable>();
//    auto fps = rs.getRenderable<TextRenderable>(0);
//    fps.accTextState().setText("FPS: "+string_utils::toString(game.getFPS()));
//
//    auto ups = rs.getRenderable<TextRenderable>(1);
//    ups.accTextState().setText("UPS: "+string_utils::toString(game.getUPS()));
//
//    auto particles_label = rs.getRenderable<TextRenderable>(2);
//    u32 particles_cnt = game.getModule<Window>().getVertices().getFast<VertexDataParticles>().getParticlesCount();
//    particles_label.accTextState().setText("Particles: "+string_utils::toString(particles_cnt));


//    auto ps = rs.getPartRenderable<ParticlesRenderable>(pStars);
//    Colorf clrs[] = {
//            Color(162, 232, 220).toFloat(),
//            Color(255, 220, 203).toFloat(),
//            Color(246, 253, 166).toFloat(),
//            Colorf::White()
//    };
//    for (u32 i=0; i< 15; ++i) {
//        Angle a(-randFloat()*Angle::Pi);
//        Vec2 speed = a.getDir()*(randFloat()*10);
//
//        ps.addParticle({randFloat()*1024, randFloat()*768},
//                       Angle::random(),
//                       Angle::random() *0.5f,
//                       clrs[rand()%ARRAY_SIZE(clrs)],
//                       speed,
//                       randFloat()*2,
//                       0);
//    }
}