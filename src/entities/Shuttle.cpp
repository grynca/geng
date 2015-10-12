#include "incl.h"
#include "Shuttle.h"
#include "../MyAssets.h"

TextureRegion Shuttle::sprite_region;

Shuttle::Shuttle() {

}

void Shuttle::initResources(MyGame& game) {
    sprite_region = *game.getModule<AssetsManager>().getImageRegion("data/sprites/shuttle.png");
}

GameEntity& Shuttle::create(MyGame& game) {
//static
    GameEntity& ent = game.getSysEnt().getEntityManager().addItem();
    ent.setRoles({EntityRoles::erRenderable, EntityRoles::erMovable});
    Shuttle& me = ent.set<Shuttle>();

    ImageRenderable & sr = me.getRenderables().add<ImageRenderable>().init(game, 3, 0, sprite_region.getTextureRect(), Vec2{100, 100});
    return ent;
}


void Shuttle::update(MyGame& game) {
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

    getTransform().setRotation(shuttle_motion.getAngle());

    shuttle_motion *= shuttle_speed;

    getSpeed().setLinearSpeed(shuttle_motion);
}