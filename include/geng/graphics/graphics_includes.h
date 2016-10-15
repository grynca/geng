#ifndef GRAPHICS_INCLUDES_H
#define GRAPHICS_INCLUDES_H

#include "graphics_config.h"
#include "Vertices.h"
#include "VertexData.h"
#include "Geom.h"
#include "geng/graphics/VertexData/Factories/geom_factories.h"
#include "Shaders.h"
#include "Shader.h"
#include "Window.h"
#include "ViewPort.h"
#include "geng/graphics/Renderables/RenderableBase.h"
#include "Renderer2D.h"
#include "Texture2D.h"
#include "CoordFrame.h"
#include "Textures2DManager.h"
#include "Events.h"
#include "Shaders/CircleShader.h"
#include "geng/graphics/Shaders/SimpleColorShader.h"
#include "Shaders/RectBorderShader.h"
#include "geng/graphics/Shaders/SimpleTexturedShader.h"
#include "Shaders/TextShader.h"
#include "VertexData/VertexDataPT.h"
#include "VertexData/VertexDataP.h"

#include "Components/CRenderables.h"
#if GENG_PHYSICS == 1
# include "Systems/CollisionsDebugSystem.h"
#endif
#include "Systems/RenderSystem.h"

#endif //GRAPHICS_INCLUDES_H
