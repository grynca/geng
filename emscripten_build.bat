mkdir build
cd build
mkdir Emscripten
cd ..
set EMCC_DEBUG=2

set IDIRS= -Iinclude -Isrc -Ic:/DEV/gamedev/base/src -Ic:/DEV/gamedev/maths/src -Ic:/DEV/gamedev/assets/include -Ic:/DEV/gamedev/SAP/include -Ic:/DEV/gamedev/sysent/include -Ic:/DEV/gamedev/ggnet/include -Ic:/DEV/libs/mingw/glm -Ic:/DEV/libs/emscripten/freetype-2.5.5/include
set LDIRS= -Lc:/DEV/libs/emscripten/freetype-2.5.5/objs/.libs
set LIBS="-lfreetype"
set FLAGS= -std=c++11 -DWEB -DGLM_FORCE_RADIANS %IDIRS% -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_LIBPNG=1 -s TOTAL_MEMORY=134217728 --use-preload-plugins --preload-file data -O3

set GENG_SOURCES= include/geng/graphics/Events.cpp include/geng/graphics/GraphicsDomain.cpp include/geng/graphics/Shader.cpp include/geng/graphics/Texture2D.cpp include/geng/graphics/ViewPort.cpp include/geng/graphics/Window.cpp include/geng/physics/PhysicsDomain.cpp
set TEST_SOURCES= src/entities/MyEntity.cpp src/entities/Shuttle.cpp src/entities/HUD.cpp src/MyGame.cpp src/main.cpp

call emcc %GENG_SOURCES% %FLAGS% -o build/Emscripten/geng.bc
call emcc %TEST_SOURCES% %FLAGS% -o build/Emscripten/test.bc

call emcc build/Emscripten/geng.bc build/Emscripten/test.bc %FLAGS% %LDIRS% %LIBS% -o build/Emscripten/main.html
