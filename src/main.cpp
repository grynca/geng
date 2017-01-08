#include "incl.h"

int main(int argc, char* argv[]) {
    MyGame& g = MyGame::createAs<MyGame>();
    g.initEM<EntityTypes>(10000);
    g.start();

#ifdef PROFILE_BUILD
    std::cout << g.getEntitiesManager().getProfileString() << std::endl;
#endif
    WAIT_FOR_KEY_ON_WIN();
    return 0;
}