#ifndef GRAPHICS_INCLUDES_H
#define GRAPHICS_INCLUDES_H

#include "graphics_config.h"
#include "Vertices.h"
#include "VertexData/VertexData.h"
#include "VertexData/Geom.h"
#include "VertexData/VertexDataPT.h"
#include "VertexData/VertexDataP.h"
#include "VertexData/VertexDataParticles.h"
#include "VertexData/Factories/geom_factories.h"
#include "Shaders.h"
#include "Shader.h"
#include "Window.h"
#include "ViewPort.h"
#include "geng/graphics/Renderables/RenderIndex.h"
#include "Renderables/CircleRenderable.h"
#include "Renderables/RectRenderable.h"
#include "Renderables/RectBorderRenderable.h"
#include "Renderables/PgonRenderable.h"
#include "Renderables/PgonTexturedRenderable.h"
#include "Renderables/SpriteRenderable.h"
#include "Renderables/TextRenderable.h"
#include "Renderables/ParticlesRenderable.h"
#include "Renderer2D.h"
#include "Texture2D.h"
#include "CoordFrame.h"
#include "Textures2DManager.h"
#include "Events.h"
#include "Shaders/CircleShader.h"
#include "Shaders/SimpleColorShader.h"
#include "Shaders/RectBorderShader.h"
#include "Shaders/SimpleTexturedShader.h"
#include "Shaders/TextShader.h"
#include "Shaders/ParticleShader.h"

#include "Components/CRenderables.h"
#include "Entities/GUIElement.h"
#if GENG_PHYSICS == 1
# include "Systems/CollisionsDebugSystem.h"
#endif
#include "Systems/RenderSystem.h"

#endif //GRAPHICS_INCLUDES_H
