#include "sysent.h"
#include "Shuttle.h"

Shuttle::Shuttle() {

}

void Shuttle::initResources(Game& game) {
// static
    Texture2D& t = game.getModule<Window>().getTextures().addItem("shuttle");
    t.bind(1);
    t.set(RefPtr<Image>(new Image("data/shuttle.png")));
}

Entity& Shuttle::create(Game& game) {
//static
    Entity& ent = game.getModule<EntityManager>().addItem();
    ent.setRoles({erRenderable, erMovable});
    Shuttle& me = ent.set<Shuttle>();

    SpriteRenderable & sr = me.renderables.add<SpriteRenderable>(game.getModule<Window>(), 3, 1, Vec2{100, 100});

    return ent;
}


void Shuttle::update(Game& game) {
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

    transform.setRotation(shuttle_motion.getAngle());

    shuttle_motion *= shuttle_speed;

    speed.setLinearSpeed(shuttle_motion);
}