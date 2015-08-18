mkdir build
cd build
mkdir Emscripten
cd ..
set EMCC_DEBUG=2

set IDIRS= -Iinclude -Isrc -Ic:/DEV/gamedev/base/src -Ic:/DEV/gamedev/maths/src -Ic:/DEV/gamedev/assets/include -Ic:/DEV/gamedev/sysent/src -Ic:/DEV/libs/mingw/glm
set FLAGS= -std=c++11 -DWEB -DGLM_FORCE_RADIANS %IDIRS% -s USE_SDL=2 -s USE_SDL_IMAGE=2
set GENG_SOURCES= include/geng/Game.cpp include/geng/graphics/Window.cpp include/geng/graphics/Shader.cpp include/geng/graphics/Texture2D.cpp include/geng/graphics/Textures2DManager.cpp include/geng/graphics/Graphics.cpp include/geng/graphics/ViewPort.cpp include/geng/graphics/Events.cpp include/geng/physics/Physics.cpp
set TEST_SOURCES= src/entities/MyEntity.cpp src/entities/Shuttle.cpp src/main.cpp

call emcc %GENG_SOURCES% %FLAGS% -o build/Emscripten/geng.bc
call emcc %TEST_SOURCES% %FLAGS% -o build/Emscripten/test.bc

call emcc build/Emscripten/geng.bc build/Emscripten/test.bc %FLAGS% --preload-file data  -o build/Emscripten/main.html
