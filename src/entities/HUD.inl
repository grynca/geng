#include "../incl.h"
#include "HUD.h"

inline HUD::Resources::Resources(GameBase& game) {
    AssetsManager& am = game.getModule<AssetsManager>();
    particle_region = *am.getImageRegion("data/sprites/particle_rp.png");
}

inline void HUD::init(Entity& ent, GameBase& game) {
// static
    CRenderables& rs = ent.getComponent<CRenderables>();
    TextRenderable fps = rs.addRenderable<TextRenderable>();
    fps.accRenderTask()->setLayer(10);
    fps.accRenderTask()->setCoordFrame(cfScreenGlobal);
    fps.setColor(Colorf::White());
    fps.setTextureUnit(1);
    fps.accTextState().setFont("arial", 30).setText("FPS: ");
    fps.setPosition({10, 40});

    TextRenderable ups = rs.addRenderable<TextRenderable>();
    ups.accRenderTask()->setLayer(10);
    ups.accRenderTask()->setCoordFrame(cfScreenGlobal);
    ups.setColor(Colorf::White());
    ups.setTextureUnit(1);
    ups.accTextState().setFont("arial", 30).setText("UPS: ");
    ups.setPosition({10, 90});

    TextRenderable particles_label = rs.addRenderable<TextRenderable>();
    particles_label.accRenderTask()->setLayer(10);
    particles_label.accRenderTask()->setCoordFrame(cfScreenGlobal);
    particles_label.setColor(Colorf::White());
    particles_label.setTextureUnit(1);
    particles_label.accTextState().setFont("arial", 30).setText("Particles: ");
    particles_label.setPosition({500, 40});

    ParticlesRenderable ps = rs.addRenderable<ParticlesRenderable>();
    ps.accRenderTask()->setLayer(1);
    ps.accRenderTask()->setCoordFrame(cfScreenGlobal);

    ps.setGravityDir({0, 1.0f});
    ps.setMaxTime(30);
    ps.setParticlesSize({20, 30});
    ps.setTextureUnit(0);
    ps.setTextureRegion(Resources::get().particle_region.getTextureRect());
}

inline void HUD::update(Entity& e, GameBase& game) {
//static
    CRenderables& rs = e.getComponent<CRenderables>();
    auto fps = rs.getRenderable<TextRenderable>(0);
    fps.accTextState().setText("FPS: "+string_utils::toString(game.getFPS()));

    auto ups = rs.getRenderable<TextRenderable>(1);
    ups.accTextState().setText("UPS: "+string_utils::toString(game.getUPS()));

    auto particles_label = rs.getRenderable<TextRenderable>(2);
    u32 particles_cnt = game.getModule<Window>().getVertices().get<VertexDataParticles>().getParticlesCount();
    particles_label.accTextState().setText("Particles: "+string_utils::toString(particles_cnt));


    ParticlesRenderable ps = rs.getRenderable<ParticlesRenderable>(3);
    Colorf clrs[] = {
            Color(162, 232, 220).toFloat(),
            Color(255, 220, 203).toFloat(),
            Color(246, 253, 166).toFloat(),
            Colorf::White()
    };
    for (u32 i=0; i< 15; ++i) {
        Angle a(-randFloat()*Angle::Pi);
        Vec2 speed = a.getDir()*(randFloat()*10);

        ps.addParticle({randFloat()*1024, randFloat()*768},
                       Angle::random(),
                       Angle::random() *0.5f,
                       clrs[rand()%ARRAY_SIZE(clrs)],
                       speed,
                       randFloat()*2,
                       0);
    }
}