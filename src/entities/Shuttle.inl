#include "../incl.h"
#include "Shuttle.h"

inline Shuttle::Resources::Resources(GameBase& game) {
    AssetsManager& am = game.getModule<AssetsManager>();
    sprite_region = *am.getImageRegion("data/sprites/shuttle.png");
    particle_region = *am.getImageRegion("data/sprites/particle_rp.png");
}

inline void Shuttle::init(Entity& ent, GameBase& game) {
//static

    CRenderables& rs = ent.getComponent<CRenderables>();

    auto sr = rs.addRenderable<SpriteRenderable>();
    sr.accRenderTask()->setLayer(3);
    sr.setTextureUnit(0);
    sr.setImageRegion(Resources::get().sprite_region.getTextureRect());
    sr.setSize(Resources::get().sprite_region.getRect().getSize()*0.5);

    auto pr = rs.addRenderable<ParticlesRenderable>();
    pr.accRenderTask()->setLayer(3);
    pr.accRenderTask()->setCoordFrame(cfWorldGlobal);
    pr.setGravityDir({0, 0});
    pr.setMaxTime(0.8f);
    pr.setParticlesSize({12, 35});
    pr.setTextureUnit(0);
    pr.setTextureRegion(Resources::get().particle_region.getTextureRect());

    CBody& cb = ent.getComponent<CBody>();
    Collidable& coll = cb.addCollidable();
    coll.boundSprite(sr);
}

inline void Shuttle::update(Entity& e, GameBase& game) {
// static
    static int shuttle_speed = 100;

    Events& events = game.getModule<Window>().getEvents();

    Vec2 shuttle_motion;
    shuttle_motion.accX() -= (int)events.isKeyDown(SDL_SCANCODE_A);
    shuttle_motion.accX() += (int)events.isKeyDown(SDL_SCANCODE_D);
    shuttle_motion.accY() -= (int)events.isKeyDown(SDL_SCANCODE_W);
    shuttle_motion.accY() += (int)events.isKeyDown(SDL_SCANCODE_S);
    if (shuttle_motion.getX() && shuttle_motion.getY()) {
        static f32 norm = 1.f/(f32)sqrt(2);
        shuttle_motion *= norm;
    }

    if (shuttle_motion.isZero()) {
        CMovable& m = e.getComponent<CMovable>();
        m.getSpeed().setLinearSpeed({0, 0});
    }
    else {
        CTransform& t = e.getComponent<CTransform>();
        if (t.get().getRotation() != shuttle_motion.getAngle())
            t.setRotation(shuttle_motion.getAngle(), e);

        shuttle_motion *= shuttle_speed;
        CMovable& m = e.getComponent<CMovable>();
        m.getSpeed().setLinearSpeed(shuttle_motion);

        // tail particles
        CRenderables& rs = e.getComponent<CRenderables>();
        Vec2 shuttle_size = rs.getRenderable<SpriteRenderable>(0).getSize();
        auto particles = rs.getRenderable<ParticlesRenderable>(1);
        Colorf ps_clrs[] = {
                Color(237, 0, 28).toFloat(),
                Color(247, 63, 0).toFloat(),
                Color(247, 137, 133).toFloat(),
                Color(242, 253, 35).toFloat()
        };
        Mat3 tr_m = t.get().calcMatrix();
        for (u32 i=0; i< 12; ++i) {

            Vec2 pos(-0.5f*shuttle_size.getX(), ((randFloat()-0.5f)*shuttle_size.getY()));
            Angle speed_angle(randFloatMinMax(-0.15f*Angle::Pi, 0.15f*Angle::Pi));
            Dir2 speed = speed_angle.getDir();
            particles.addParticle(tr_m*pos,
                                  Angle::random(),
                                  randFloatMinMax(0, Angle::Pi),
                                  ps_clrs[rand()%ARRAY_SIZE(ps_clrs)],
                                  (tr_m*speed)*(-randFloat()*150),
                                  randFloat()*5,
                                  randFloat()*0.3f);
        }
    }
}