#include <iostream>
#include "geng.h"
#include "MyGame.h"
#include "MyAssets.h"


using namespace std;
using namespace grynca;


int main(int argc, char* argv[]) {
    MyGame::create().start();
    return 0;
}