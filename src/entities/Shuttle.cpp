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
    Shuttle& me = ent.set<Shuttle>();

    SpriteRenderable & sr = me.getRenderables().add<SpriteRenderable>(game);
    sr.setLayerId(3);
    sr.setTextureUnit(0);
    sr.setImageRegion(sprite_region);
    sr.getLocalTransform().setScale(Vec2{0.5, 0.5});
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

    if (getTransform().getRotation() != shuttle_motion.getAngle())
        setRotation(shuttle_motion.getAngle());

    shuttle_motion *= shuttle_speed;

    getSpeed().setLinearSpeed(shuttle_motion);

    //std::cout << "shuttle flags: " << getFlags() << std::endl;
}