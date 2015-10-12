#include "MyGame.h"
#include "MyAssets.h"
#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"

using namespace std;
using namespace grynca;


void MyGame::init() {
#ifndef WEB
    getModule<Window>().setVSync(true);
#endif
    MyAssets::init(*this);

    MyEntity::initResources(*this);
    Shuttle::initResources(*this);

    test_ent = &MyEntity::create(*this);
    shuttle = &Shuttle::create(*this);
    hud = &HUD::create(*this);
}

void MyGame::update() {
    test_ent->get<MyEntity>().update();
    shuttle->get<Shuttle>().update(*this);
    hud->get<HUD>().update(*this);

    Events& events = getModule<Window>().getEvents();
    bool alt_down = events.isKeyDown(SDL_SCANCODE_LALT)|events.isKeyDown(SDL_SCANCODE_RALT);
    if (events.wasKeyPressed(SDL_SCANCODE_F4) && alt_down)
        quit();
    else if (events.wasKeyPressed(SDL_SCANCODE_RETURN) && alt_down)
        getModule<Window>().toggleFullscreen();

    static float camera_l_speed = (float)100/60;
    Vec2 camera_motion;
    camera_motion.accX() -= (int)events.isKeyDown(SDL_SCANCODE_LEFT);
    camera_motion.accX() += (int)events.isKeyDown(SDL_SCANCODE_RIGHT);
    camera_motion.accY() -= (int)events.isKeyDown(SDL_SCANCODE_UP);
    camera_motion.accY() += (int)events.isKeyDown(SDL_SCANCODE_DOWN);
    if (camera_motion.getX() && camera_motion.getY()) {
        static float norm = 1.f/(float)sqrt(2);
        camera_motion *= norm;
    }
    camera_motion *= camera_l_speed;
    getModule<Window>().getViewPort().moveRelative(camera_motion);
}

void MyGame::tick() {

}