#ifndef RENDERABLES_INCLUDES_H
#define RENDERABLES_INCLUDES_H

#include "RenderBatchId.h"
#include "CircleRenderable.h"
#include "RectRenderable.h"
#include "RectBorderRenderable.h"
#include "PgonRenderable.h"
#include "PgonTexturedRenderable.h"
#include "SpriteRenderable.h"
#include "TextRenderable.h"
#include "ParticlesRenderable.h"

typedef grynca::TypesPack<
        CircleRenderable,
        RectRenderable,
        RectBorderRenderable,
        PgonRenderable,
        PgonTexturedRenderable,
        SpriteRenderable,
        TextRenderable,
        ParticlesRenderable
> RenderableTypes;


#endif //RENDERABLES_INCLUDES_H
