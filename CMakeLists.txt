cmake_minimum_required(VERSION 3.2)
project(geng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS -std=c++14 -ffast-math" )

IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    #disable profiling
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNPROFILE -Wall -Werror -Wno-strict-aliasing" )
ENDIF()

IF (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    IF (WIN32)
        # for profiling
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -gdwarf-2" )
    ENDIF()
ENDIF()

IF (WIN32)
    include_directories(c:/DEV/gamedev/base/src/)
    include_directories(c:/DEV/gamedev/maths/include/)
    include_directories(c:/DEV/gamedev/sysent/include/)
    include_directories(c:/DEV/gamedev/SAP/include/)
    include_directories(c:/DEV/gamedev/assets/include/)
    include_directories(c:/DEV/gamedev/ggnet/include/)
    include_directories(c:/DEV/libs/mingw/glm/)
    include_directories(c:/DEV/libs/mingw/glew-1.13.0/include/)
    link_directories(c:/DEV/libs/mingw/glew-1.13.0/lib/)
    include_directories(c:/DEV/libs/mingw/freetype-2.6/include/)
    link_directories(c:/DEV/libs/mingw/freetype-2.6/lib/)
    include_directories(c:/DEV/libs/mingw/SDL2-2.0.4/x86/include/)
    link_directories(c:/DEV/libs/mingw/SDL2-2.0.4/x86/lib)

    set(LIBS "-lfreetype -lglew32 -lglu32 -lopengl32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lws2_32")
ELSE()
    include_directories(/home/grynca/DEV/gamedev/base/src)
    include_directories(/home/grynca/DEV/gamedev/sysent/include/)
    include_directories(/home/grynca/DEV/gamedev/maths/include/)
    include_directories(/home/grynca/DEV/gamedev/SAP/include/)
    include_directories(/home/grynca/DEV/gamedev/assets/include/)
    include_directories(/home/grynca/DEV/gamedev/ggnet/include/)
    include_directories(/usr/include/freetype2)

    set(LIBS "-lGLEW -lGL -lGLU -lfreetype -lSDL2 -lSDL2_image")
ENDIF()
include_directories(include/)

set(GENG_SOURCES
        include/geng/graphics/graphics_includes.h
        include/geng/graphics/graphics_config.h
        include/geng/graphics/glinclude.h
        include/geng/graphics/Window.h
        include/geng/graphics/Window.inl
        include/geng/graphics/Shader.h
        include/geng/graphics/Shader.inl
        include/geng/graphics/VertexData/VertexData.h
        include/geng/graphics/VertexData/VertexData.inl
        include/geng/graphics/VertexData/GeomState.h
        include/geng/graphics/VertexData/Geom.h
        include/geng/graphics/VertexData/Geom.inl
        include/geng/graphics/VertexData/VertexDataPT.h
        include/geng/graphics/VertexData/VertexDataPT.inl
        include/geng/graphics/VertexData/VertexDataP.h
        include/geng/graphics/VertexData/VertexDataParticles.h
        include/geng/graphics/VertexData/VertexDataParticles.inl
        include/geng/graphics/VertexData/Factories/geom_factories.h
        include/geng/graphics/VertexData/Factories/FactoryRectTF.h
        include/geng/graphics/VertexData/Factories/FactoryRectTF.inl
        include/geng/graphics/VertexData/Factories/FactoryRectT.h
        include/geng/graphics/VertexData/Factories/FactoryRectT.inl
        include/geng/graphics/VertexData/SpriteAnimationStates.h
        include/geng/graphics/VertexData/SpriteAnimationStates.inl
        include/geng/graphics/VertexData/TextStates.h
        include/geng/graphics/VertexData/TextStates.inl
        include/geng/graphics/VertexData/ParticleBatchStates.h
        include/geng/graphics/VertexData/ParticleBatchStates.inl
        include/geng/graphics/Vertices.h
        include/geng/graphics/Vertices.inl
        include/geng/graphics/Renderer2D.h
        include/geng/graphics/Renderer2D.inl
        include/geng/graphics/Texture2D.h
        include/geng/graphics/Texture2D.inl
        include/geng/graphics/Textures2DManager.h
        include/geng/graphics/Textures2DManager.inl
        include/geng/graphics/Shaders.h
        include/geng/graphics/Shaders.inl
        include/geng/graphics/Shaders/CircleShader.h
        include/geng/graphics/Shaders/SimpleColorShader.h
        include/geng/graphics/Shaders/SimpleTexturedShader.h
        include/geng/graphics/Shaders/TextShader.h
        include/geng/graphics/Shaders/RectBorderShader.h
        include/geng/graphics/Shaders/ParticleShader.h
        include/geng/graphics/Renderables/RenderIndex.h
        include/geng/graphics/Renderables/RenderIndex.inl
        include/geng/graphics/Renderables/Renderable.h
        include/geng/graphics/Renderables/Renderable.inl
        include/geng/graphics/Renderables/CircleRenderable.h
        include/geng/graphics/Renderables/CircleRenderable.inl
        include/geng/graphics/Renderables/SpriteRenderable.h
        include/geng/graphics/Renderables/SpriteRenderable.inl
        include/geng/graphics/Renderables/RectRenderable.h
        include/geng/graphics/Renderables/RectRenderable.inl
        include/geng/graphics/Renderables/RectBorderRenderable.h
        include/geng/graphics/Renderables/RectBorderRenderable.inl
        include/geng/graphics/Renderables/TextRenderable.h
        include/geng/graphics/Renderables/TextRenderable.inl
        include/geng/graphics/Renderables/RectBorderRenderable.h
        include/geng/graphics/Renderables/PgonRenderable.h
        include/geng/graphics/Renderables/PgonRenderable.inl
        include/geng/graphics/Renderables/PgonTexturedRenderable.h
        include/geng/graphics/Renderables/PgonTexturedRenderable.inl
        include/geng/graphics/Renderables/ParticlesRenderable.h
        include/geng/graphics/Renderables/ParticlesRenderable.inl
        include/geng/graphics/Entities/GUIElement.h
        include/geng/graphics/Components/CRenderables.h
        include/geng/graphics/Systems/RenderSystem.h
        include/geng/graphics/Systems/RenderSystem.inl
        include/geng/graphics/Systems/CollisionsDebugSystem.h
        include/geng/graphics/Systems/CollisionsDebugSystem.inl
        include/geng/graphics/CoordFrame.h
        include/geng/graphics/ViewPort.h
        include/geng/graphics/ViewPort.inl
        include/geng/graphics/Events.h
        include/geng/graphics/Events.inl
        include/geng/graphics/GUI.h
        include/geng/graphics/GUI.inl

        include/geng/network/network_includes.h
        include/geng/network/Snapshots.h
        include/geng/network/Snapshots.inl
        include/geng/network/ClientStateBase.h
        include/geng/network/Components/CNetworked.h
        include/geng/network/Systems/ServerNetworkSystem.h
        include/geng/network/Systems/ServerNetworkSystem.inl
        include/geng/network/Systems/ClientNetworkSystem.h
        include/geng/network/Systems/ClientNetworkSystem.inl

        include/geng/physics/physics_includes.h
        include/geng/physics/Collidable.h
        include/geng/physics/Components/CBody.h
        include/geng/physics/Systems/CollisionSystem.h
        include/geng/physics/Systems/CollisionSystem.inl

        include/geng/core/core_includes.h
        include/geng/core/Components/CTransform.h
        include/geng/core/Components/CTransform.inl
        include/geng/core/Components/CMovable.h
        include/geng/core/Components/CDeltaTransform.h
        include/geng/core/Components/CDeltaTransform.inl
        include/geng/core/Speed.h
        include/geng/core/GengSystem.h
        include/geng/core/GengEntity.h
        include/geng/core/Systems/MovementSystem.h
        include/geng/core/Systems/DeltaTransformSystem.h

        include/geng/sdlinclude.h
        include/geng/GameBase.h
        include/geng/GameBase.inl
        include/geng/Game.h
        include/geng/Game.inl
        include/geng/GEFlags.h
        include/geng/GERoles.h
        include/geng/geng_config.h
        include/geng_enums.h
        include/geng.h
        )

set(TEST_SOURCES
        src/main.cpp
        src/incl.h
        src/entities/MyEntity.h
        src/entities/MyEntity.inl
        src/entities/Shuttle.h
        src/entities/Shuttle.inl
        src/entities/HUD.h
        src/entities/HUD.inl
        src/MyGame.h
        src/MyGame.inl
        )

#add_library(geng ${GENG_SOURCES})
add_executable(basic ${GENG_SOURCES} ${TEST_SOURCES})
target_link_libraries(basic ${LIBS})