#include <iostream>
#include "base.h"
#include "geng.h"
#include "sysent.h"

using namespace std;
using namespace grynca;

class MyGame : public Game, public Singleton<MyGame> {
public:

private:
    Entity* me;
    Entity* shuttle;

    virtual void init() override {
#ifndef WEB
        getModule<Window>().setVSync(true);
#endif
        MyEntity::initResources(*this);
        Shuttle::initResources(*this);

        me = &MyEntity::create(*this);
        shuttle = &Shuttle::create(*this);
    }

    virtual void update() override {
        me->get<MyEntity>().update();
        shuttle->get<Shuttle>().update(*this);

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

    virtual void tick() override {
        std::cout << "FPS: " << getFPS() << std::endl;
        std::cout << "UPS: " << getUPS() << std::endl;
    }
};

int main(int argc, char* argv[]) {
    MyGame::create().start();
    return 0;
}