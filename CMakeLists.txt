cmake_minimum_required(VERSION 3.2)
project(geng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++0x" )
# for profiling
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -gdwarf-2" )

include_directories(c:/DEV/gamedev/base/src/)
include_directories(c:/DEV/gamedev/sysent/src/)
include_directories(c:/DEV/gamedev/maths/src/)
include_directories(c:/DEV/gamedev/assets/include/)
include_directories(include/)
include_directories(src/)
include_directories(include/geng/setup/)
#glew
include_directories(c:/DEV/libs/mingw/glew-1.12.0/include/)
link_directories(c:/DEV/libs/mingw/glew-1.12.0/lib/)
#sdl
include_directories(c:/DEV/libs/mingw/SDL2-2.0.3/include/)
link_directories(c:/DEV/libs/mingw/SDL2-2.0.3/build/.libs/)
#sdl-image
include_directories(c:/DEV/libs/mingw/SDL2_image-2.0.0/)
link_directories(c:/DEV/libs/mingw/SDL2_image-2.0.0/.libs/)
#glm
include_directories(c:/DEV/libs/mingw/glm/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS" )

set(LIBS "-lglew32 -lopengl32 -lglu32
          -lmingw32 -lSDL2main -lSDL2 -lSDL2_image")

set(SOURCE_FILES
    include/geng/setup/geng_entities.h
    include/geng/setup/geng_systems.h
    include/geng/sdlinclude.h
    include/geng/Game.h
    include/geng/Game.inl
    include/geng/Game.cpp
    include/geng.h

    include/geng/graphics/graphics_config.h
    include/geng/graphics/glinclude.h
    include/geng/graphics/ftinclude.h
    include/geng/graphics/Window.h
    include/geng/graphics/Window.cpp
    include/geng/graphics/Shader.h
    include/geng/graphics/Shader.cpp
    include/geng/graphics/VertexData.h
    include/geng/graphics/VertexData.inl
    include/geng/graphics/Geom.h
    include/geng/graphics/Geom.inl
    include/geng/graphics/geom_utils.h
    include/geng/graphics/Vertices.h
    include/geng/graphics/Vertices.inl
    include/geng/graphics/Renderer2D.h
    include/geng/graphics/Renderer2D.inl
    include/geng/graphics/Texture2D.h
    include/geng/graphics/Texture2D.cpp
    include/geng/graphics/Textures2DManager.h
    include/geng/graphics/Textures2DManager.cpp
    include/geng/graphics/Shaders.h
    include/geng/graphics/Shaders.inl
    include/geng/graphics/Shaders/CircleShader.h
    include/geng/graphics/Shaders/RectShader.h
    include/geng/graphics/Shaders/SpriteShader.h
    include/geng/graphics/VertexData/VertexDataPT.h
    include/geng/graphics/VertexData/VertexDataP.h
    include/geng/graphics/Renderable.h
    include/geng/graphics/Renderable.inl
    include/geng/graphics/Renderables/CircleRenderable.h
    include/geng/graphics/Renderables/SpriteRenderable.h
    include/geng/graphics/Renderables/RectRenderable.h
    include/geng/graphics/DrawSortingKey.h
    include/geng/graphics/systems/RenderSystem.h
    include/geng/graphics/systems/RenderSystem.inl
    include/geng/graphics/Graphics.h
    include/geng/graphics/Graphics.cpp
    include/geng/graphics/graphics_includes.h
    include/geng/graphics/Frame.h
    include/geng/graphics/ViewPort.h
    include/geng/graphics/ViewPort.cpp
    include/geng/graphics/Events.h
    include/geng/graphics/Events.cpp

    include/geng/physics/Speed.h
    include/geng/physics/physics_includes.h
    include/geng/physics/Physics.h
    include/geng/physics/Physics.cpp
    include/geng/physics/systems/MovementSystem.h

    src/basic.cpp
    src/entities/MyEntity.h
    src/entities/MyEntity.cpp
    )
add_executable(basic ${SOURCE_FILES})
target_link_libraries(basic ${LIBS})