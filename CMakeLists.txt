cmake_minimum_required(VERSION 3.2)
project(geng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS -std=c++11 -std=gnu++0x" )
# for profiling
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -gdwarf-2" )

include_directories(/home/grynca/DEV/gamedev/base/src)
include_directories(/home/grynca/DEV/gamedev/sysent/include/)
include_directories(/home/grynca/DEV/gamedev/maths/src/)
include_directories(/home/grynca/DEV/gamedev/assets/include/)
include_directories(include/)
include_directories(src/)

include_directories(/usr/include/freetype2)


set(LIBS "-lGLEW -lGL -lGLU -lfreetype -lSDL2 -lSDL2_image")

set(GENG_SOURCES
        include/geng/graphics/graphics_config.h
        include/geng/graphics/glinclude.h
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
        include/geng/graphics/Shaders/TextShader.h
        include/geng/graphics/VertexData/VertexDataPT.h
        include/geng/graphics/VertexData/VertexDataP.h
        include/geng/graphics/Renderable.h
        include/geng/graphics/Renderable.inl
        include/geng/graphics/Renderables/CircleRenderable.h
        include/geng/graphics/Renderables/CircleRenderable.inl
        include/geng/graphics/Renderables/ImageRenderable.h
        include/geng/graphics/Renderables/ImageRenderable.inl
        include/geng/graphics/Renderables/SpriteRenderable.h
        include/geng/graphics/Renderables/SpriteRenderable.inl
        include/geng/graphics/Renderables/RectRenderable.h
        include/geng/graphics/Renderables/RectRenderable.inl
        include/geng/graphics/Renderables/TextRenderable.h
        include/geng/graphics/Renderables/TextRenderable.inl
        include/geng/graphics/DrawSortingKey.h
        include/geng/ES/RenderSystem.h
        include/geng/ES/RenderSystem.inl
        include/geng/graphics/GraphicsDomain.h
        include/geng/graphics/GraphicsDomain.cpp
        include/geng/graphics/graphics_includes.h
        include/geng/graphics/CoordFrame.h
        include/geng/graphics/ViewPort.h
        include/geng/graphics/ViewPort.cpp
        include/geng/graphics/Events.h
        include/geng/graphics/Events.cpp

        include/geng/ES/ENonMovable.h
        include/geng/ES/EMovable.h
        include/geng/ES/ERenderables.h
        include/geng/ES/GengEntityRoles.h
        include/geng/ES/GengSystemTypes.h
        include/geng/ES/GengEntityTypes.h
        include/geng/ES/GameSystem.h
        include/geng/ES/MovementSystem.h
        include/geng/ES/ES_includes.h
        include/geng/ES/ES.h

        include/geng/physics/Speed.h
        include/geng/physics/physics_includes.h
        include/geng/physics/Physics.h
        include/geng/physics/Physics.cpp

        include/geng/sdlinclude.h
        include/geng/Game.h
        include/geng/Game.inl
        include/geng.h
)

set(TEST_SOURCES
        src/main.cpp
        src/incl.h
        src/entities/MyEntity.h
        src/entities/MyEntity.cpp
        src/entities/Shuttle.h
        src/entities/Shuttle.cpp
        src/MyAssets.h
        src/entities/HUD.h
        src/entities/HUD.cpp
        src/MyGame.h
        src/MyGame.cpp)

add_library(geng ${GENG_SOURCES})
add_executable(basic ${GENG_SOURCES} ${TEST_SOURCES})
target_link_libraries(basic ${LIBS})