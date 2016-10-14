#include "../incl.h"
#include "Shuttle.h"

TextureRegion Shuttle::sprite_region;

void Shuttle::initResources(MyGame& game) {
    sprite_region = *game.getModule<AssetsManager>().getImageRegion("data/sprites/shuttle.png");
}

Entity Shuttle::create(MyGame& game) {
//static
    Entity ent = game.createEntity(GET_ETYPE_ID(Shuttle));

    CRenderables& rs = ent.getComponent<CRenderables>();
    SpriteRenderable& sr = rs.addRenderable<SpriteRenderable>().init(game);
    sr.setLayerId(3);
    sr.setTextureUnit(0);
    sr.setImageRegion(sprite_region);
    sr.accLocalTransform().setScale(Vec2{0.5, 0.5});

    CBody& cb = ent.getComponent<CBody>();
    Collidable& coll = cb.addCollidable();
    coll.boundSprite(sr);

    return ent;
}

void Shuttle::update(Entity& e, MyGame& game) {
    static int shuttle_speed = 100;

    Events& events = game.getModule<Window>().getEvents();

    Vec2 shuttle_motion;
    shuttle_motion.accX() -= (int)events.isKeyDown(SDL_SCANCODE_A);
    shuttle_motion.accX() += (int)events.isKeyDown(SDL_SCANCODE_D);
    shuttle_motion.accY() -= (int)events.isKeyDown(SDL_SCANCODE_W);
    shuttle_motion.accY() += (int)events.isKeyDown(SDL_SCANCODE_S);
    if (shuttle_motion.getX() && shuttle_motion.getY()) {
        static float norm = 1.f/(float)sqrt(2);
        shuttle_motion *= norm;
    }

    CTransform& t = e.getComponent<CTransform>();
    if (t.get().getRotation() != shuttle_motion.getAngle())
        t.setRotation(shuttle_motion.getAngle(), e);

    shuttle_motion *= shuttle_speed;

    CMovable& m = e.getComponent<CMovable>();
    m.getSpeed().setLinearSpeed(shuttle_motion);

    //std::cout << "shuttle flags: " << getFlags() << std::endl;
}