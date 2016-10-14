#include <iostream>
#include "geng.h"
#include "MyGame.h"


using namespace std;
using namespace grynca;


int main(int argc, char* argv[]) {
    MyGame& g = MyGame::create();
    g.initEM<EntityTypes>(10000);
    g.start();
    return 0;
}