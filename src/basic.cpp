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

    virtual void init() override {
        getModule<Window>().setVSync(true);

        MyEntity::initResources(*this);

        me = &MyEntity::create(*this);
    }

    virtual void update() override {
        me->get<MyEntity>().update();

        Events& events = getModule<Window>().getEvents();
        bool alt_down = events.isKeyDown(SDL_SCANCODE_LALT)|events.isKeyDown(SDL_SCANCODE_RALT);
        if (events.wasKeyPressed(SDL_SCANCODE_F4) && alt_down)
            quit();
        else if (events.wasKeyPressed(SDL_SCANCODE_RETURN) && alt_down)
            getModule<Window>().toggleFullscreen();
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