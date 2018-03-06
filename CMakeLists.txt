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

option(USE_SDL2 "Use SDL2" ON)
IF (USE_SDL2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_SDL2=1" )
    IF (WIN32)
        set(LIBS "-lglew32 -lglu32 -lopengl32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image")
    ELSE()
        set(LIBS "-lGLEW -lGL -lGLU -lSDL2 -lSDL2_image")
    ENDIF()
ENDIF()

IF (WIN32)
    include_directories(c:/DEV/gamedev/base/include/)
    include_directories(c:/DEV/gamedev/maths/include/)
    include_directories(c:/DEV/gamedev/sysent/include/)
    include_directories(c:/DEV/gamedev/SAP/include/)
    include_directories(c:/DEV/gamedev/assets/include/)
    include_directories(c:/DEV/gamedev/gphyx/include/)
    include_directories(c:/DEV/gamedev/ggnet/include/)
    include_directories(c:/DEV/ENV/msys64/mingw64/include/freetype2/)
    set(LIBS "${LIBS} -lfreetype -lws2_32")
ELSE()
    include_directories(/home/grynca/DEV/gamedev/base/include)
    include_directories(/home/grynca/DEV/gamedev/sysent/include/)
    include_directories(/home/grynca/DEV/gamedev/maths/include/)
    include_directories(/home/grynca/DEV/gamedev/SAP/include/)
    include_directories(/home/grynca/DEV/gamedev/assets/include/)
    include_directories(/home/grynca/DEV/gamedev/gphyx/include/)
    include_directories(/home/grynca/DEV/gamedev/ggnet/include/)
    include_directories(/usr/include/freetype2)

    set(LIBS "${LIBS} -lfreetype")
ENDIF()
include_directories(include/)

set(GENG_SOURCES
        include/geng/graphics/graphics_includes.h
        include/geng/graphics/graphics_config.h
        include/geng/graphics/graphics_entities.h
        include/geng/graphics/glinclude.h
        include/geng/graphics/Window.h
        include/geng/graphics/Window.inl
        include/geng/graphics/NormOffset.h
        include/geng/graphics/Shaders/Shader.h
        include/geng/graphics/Shaders/Shader.inl
        include/geng/graphics/VertexData/vertexdata_includes.h
        include/geng/graphics/VertexData/VertexData.h
        include/geng/graphics/VertexData/VertexData.inl
        include/geng/graphics/VertexData/GeomStates/GeomStates.h
        include/geng/graphics/VertexData/GeomStates/GeomStates.inl
        include/geng/graphics/VertexData/GeomStates/GeomStateBase.h
        include/geng/graphics/VertexData/GeomStates/GeomStateBase.inl
        include/geng/graphics/VertexData/GeomStates/GeomStateText.h
        include/geng/graphics/VertexData/GeomStates/GeomStateText.inl
        include/geng/graphics/VertexData/GeomStates/GeomStateSpriteAnimation.h
        include/geng/graphics/VertexData/GeomStates/GeomStateSpriteAnimation.inl
        include/geng/graphics/VertexData/GeomStates/GeomStateParticles.h
        include/geng/graphics/VertexData/GeomStates/GeomStateParticles.inl
        include/geng/graphics/VertexData/Geom.h
        include/geng/graphics/VertexData/Geom.inl
        include/geng/graphics/VertexData/geom_enums.h
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
        include/geng/graphics/Vertices.h
        include/geng/graphics/Vertices.inl
        include/geng/graphics/AssetsManager.h
        include/geng/graphics/AssetsManager.inl
        include/geng/graphics/Renderer2D.h
        include/geng/graphics/Renderer2D.inl
        include/geng/graphics/Texture2D.h
        include/geng/graphics/Texture2D.inl
        include/geng/graphics/Textures2DManager.h
        include/geng/graphics/Textures2DManager.inl
        include/geng/graphics/Shaders.h
        include/geng/graphics/Shaders.inl
        include/geng/graphics/Shaders/shaders_include.h
        include/geng/graphics/Shaders/CircleShader.h
        include/geng/graphics/Shaders/SimpleColorShader.h
        include/geng/graphics/Shaders/SimpleTexturedShader.h
        include/geng/graphics/Shaders/TextShader.h
        include/geng/graphics/Shaders/RectBorderShader.h
        include/geng/graphics/Shaders/ParticleShader.h
        include/geng/graphics/Renderables/renderables_includes.h
        include/geng/graphics/Renderables/RenderBatchId.h
        include/geng/graphics/Renderables/RenderBatchId.inl
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
        include/geng/graphics/Entities/EVisual.h
        include/geng/graphics/Entities/EBody.h
        include/geng/graphics/Entities/EBody.inl
        include/geng/graphics/Entities/DebugOverlay.h
        include/geng/graphics/Entities/DebugOverlay.inl
        include/geng/graphics/Components/CRenderable.h
        include/geng/graphics/Components/CRenderable.inl
        include/geng/graphics/Systems/RenderSystem.h
        include/geng/graphics/Systems/RenderSystem.inl
        include/geng/graphics/ViewPort.h
        include/geng/graphics/ViewPort.inl
        include/geng/graphics/Events.h
        include/geng/graphics/Events.inl
        include/geng/graphics/GUI.h
        include/geng/graphics/GUI.inl
        include/geng/graphics/ControlHelpers.h
        include/geng/graphics/ControlHelpers.inl

        include/geng/network/network_includes.h
        include/geng/network/Snapshots.h
        include/geng/network/Snapshots.inl
        include/geng/network/ClientStateBase.h
        include/geng/network/Components/CNetworkedServer.h
        include/geng/network/Components/CNetworkedClient.h
        include/geng/network/Systems/ServerNetworkSystem.h
        include/geng/network/Systems/ServerNetworkSystem.inl
        include/geng/network/Systems/ClientNetworkSystem.h
        include/geng/network/Systems/ClientNetworkSystem.inl

        include/geng/physics/physics_includes.h
        include/geng/physics/PhysicsManager.h
        include/geng/physics/PhysicsManager.inl
        include/geng/physics/physics_utils.h
        include/geng/physics/physics_entities.h
        include/geng/physics/motor_utils.h
        include/geng/physics/Components/CCollider.h
        include/geng/physics/Components/CCollider.inl
        include/geng/physics/Components/CBody.h
        include/geng/physics/Components/CBody.inl
        include/geng/physics/Components/CTreeJoint.h
        include/geng/physics/Components/CTreeJoint.inl
        include/geng/physics/Systems/BoundsSystem.h
        include/geng/physics/Systems/BoundsSystem.inl
        include/geng/physics/Systems/PhysicsSystem.h
        include/geng/physics/Systems/BoundsDebugRenderSystem.h
        include/geng/physics/Systems/BoundsDebugRenderSystem.inl
        include/geng/physics/Entities/ETrigger.h
        include/geng/physics/Entities/EGhost.h

        include/geng/core/core_common.h
        include/geng/core/core_includes.h
        include/geng/core/GengSystem.h
        include/geng/core/GengEntity.h
        include/geng/core/EntityResourcesManager.h
        include/geng/core/Components/CTransform.h
        include/geng/core/Components/CTransform.inl
        include/geng/core/Components/CTreeTransform.h
        include/geng/core/Components/CTreeTransform.inl
        include/geng/core/Components/CSpeed.h
        include/geng/core/Components/CSpeed.inl
        include/geng/core/Systems/MovementSystem.h
        include/geng/core/Systems/TreeTransformSystem.h
        include/geng/core/Systems/TreeTransformSystem.inl

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
        src/entities/Dude.h
        src/entities/Dude.inl
        src/MyGame.h
        src/MyGame.inl
        )

#add_library(geng ${GENG_SOURCES})
add_executable(basic ${GENG_SOURCES} ${TEST_SOURCES})
target_link_libraries(basic ${LIBS})