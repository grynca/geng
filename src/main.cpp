#include "incl.h"

int main(int argc, char* argv[]) {
    MyGame& g = MyGame::createAs<MyGame>();
    g.start();

    // destroy instance to make sure it destroys before static objects it references (TypeInfos ...)
    MyGame::destroy();

    WAIT_FOR_KEY_ON_WIN();
    return 0;
}