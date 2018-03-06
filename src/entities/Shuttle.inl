#include "../incl.h"
#include "Shuttle.h"

inline void Shuttle::Resources::initSingleton(GameBase& game) {
    const Window& w = game.getModule<Window>();
    AssetsManager& am = w.getAssets();
    shuttle_img = am.findImagePos("data/sprites/shuttle.png");
    particle_img = am.findImagePos("data/sprites/particle_rp.png");

    shuttle_params.sprite_prototype = SpriteRenderable::createSpritePrototype(shuttle_img);
    shuttle_params.size = shuttle_img.getTextureRegion()->getRect().getSize()*0.5;
    shuttle_params.material = Material::Metal();
    shuttle_params.layer_id = 3;
    shuttle_params.collision_group = MyCollGroups::cgDefaultBodyId;
    shuttle_params.collides_with.set();

    dout("Shuttle coll.gr: " << shuttle_params.collision_group << std::endl);
    dout("        coll.with: " << shuttle_params.collides_with << std::endl);
}

inline void Shuttle::init() {
    static Resources& res = Resources::get();
    static Game& game = Game::get();

    Vec2 shuttle_size = res.shuttle_img.getTextureRegion()->getRect().getSize()*0.5;
    Shuttle& shuttle = *this;
    {
        shuttle.initDynamicSpriteBody(res.shuttle_params);
    }

    EVisualTree exhaust = game.createEntity<EVisualTree>();
    {
        CRenderable rend = exhaust.get<CRenderable>();

        ParticlesRenderable* particles_r = rend.initR<ParticlesRenderable>();
        particles_r->setNewGeom();
        particles_r->setImage(res.particle_img);
        particles_r->setLayer(3);
        particles_r->accParticlesState().setGravityDir({0, 0}).setMaxTime(0.8f);
        particles_r->setParticlesSize({12, 30});

        CTreeTransform tree = exhaust.get<CTreeTransform>();
        tree.init(shuttle);
        tree.moveLocal({-0.5f * shuttle_size.getX(), 0.0f});
    }
}

inline void Shuttle::update() {
    static int shuttle_speed = 100;
    static Game& game = Game::get();

    Events& events = game.getModule<Window>().getEvents();

    Vec2 shuttle_motion = get2DMotionDir(events, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_A);
    if (shuttle_motion.isZero()) {
        CSpeedSetter spds = get<CSpeedSetter>();
        spds.accSpeed().setLinearSpeed({0, 0});
    }
    else {
        CTransformSetter trs = get<CTransformSetter>();
        if (trs.getData<CTransformData>()->getRotation() != shuttle_motion.getAngle())
            trs.setRotation(shuttle_motion.getAngle());

        shuttle_motion *= shuttle_speed;
        CSpeedSetter spds = get<CSpeedSetter>();
        spds.accSpeed().setLinearSpeed(shuttle_motion);

        // exhaust particles
        Vec2 shuttle_size = get<CRenderable>().getR<SpriteRenderable>()->getSize();
        EVisualTree exhaust = get<CTreeTransform>().getChild(0).get<EVisualTree>();
        CTreeTransform exhaust_cttr = exhaust.get<CTreeTransform>();
        ParticlesRenderable* particles_r = exhaust.get<CRenderable>().accR<ParticlesRenderable>();
        Colorf ps_clrs[] = {
                Color(237, 0, 28).toFloat(),
                Color(247, 63, 0).toFloat(),
                Color(247, 137, 133).toFloat(),
                Color(242, 253, 35).toFloat()
        };

        for (u32 i=0; i < 12; ++i) {
            Vec2 pos(0.0f, ((randFloat()-0.5f)*shuttle_size.getY()));
            Angle speed_angle = Angle::random<-27, 27>();
            Dir2 speed = speed_angle.getDir();
            particles_r->addParticle(pos,
                                     Angle::random().getDir(),
                                     speed*(-randFloat()*150),
                                     Angle::random<0, 60>(),
                                     ps_clrs[rand()%ARRAY_SIZE(ps_clrs)],
                                     randFloat()*5,
                                     randFloat()*0.3f);
        }
    }
}