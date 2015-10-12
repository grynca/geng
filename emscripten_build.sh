#!/bin/bash
mkdir -p build
cd build
mkdir -p Emscripten
cd ..
EMCC_DEBUG=2
IDIRS="-Iinclude -Isrc -I/home/grynca/DEV/gamedev/base/src -I/home/grynca/DEV/gamedev/maths/src -I/home/grynca/DEV/gamedev/assets/include -I/home/grynca/DEV/gamedev/sysent/include -I/home/grynca/DEV/libs/glm -I/home/grynca/DEV/libs/freetype-2.5.5/include"
LDIRS="-L/home/grynca/DEV/libs/freetype-2.5.5/objs/.libs"
LIBS="-lfreetype -lpng"
FLAGS="-std=c++11 -DWEB -DGLM_FORCE_RADIANS $IDIRS -s USE_SDL=2 -s USE_SDL_IMAGE=2"
GENG_SOURCES="include/geng/graphics/Window.cpp include/geng/graphics/Shader.cpp include/geng/graphics/Texture2D.cpp include/geng/graphics/Textures2DManager.cpp include/geng/graphics/Graphics.cpp include/geng/graphics/ViewPort.cpp include/geng/graphics/Events.cpp include/geng/physics/Physics.cpp"
TEST_SOURCES="src/entities/MyEntity.cpp src/entities/Shuttle.cpp src/entities/HUD.cpp src/MyGame.cpp src/main.cpp"

emcc $GENG_SOURCES $FLAGS -o build/Emscripten/geng.bc
emcc $TEST_SOURCES $FLAGS -o build/Emscripten/test.bc

emcc build/Emscripten/geng.bc build/Emscripten/test.bc $FLAGS $LDIRS $LIBS --preload-file data  -o build/Emscripten/main.html
