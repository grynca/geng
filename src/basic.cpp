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
    }

    virtual void tick() override {
        std::cout << "FPS: " << getFPS() << std::endl;
        std::cout << "UPS: " << getUPS() << std::endl;
    }
};

int main(int argc, char* argv[]) {
    MyGame::create().start();
    KEY_TO_CONTINUE();
    return 0;
}