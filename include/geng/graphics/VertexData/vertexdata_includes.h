#ifndef VERTEXDATA_INCLUDES_H
#define VERTEXDATA_INCLUDES_H

#include "VertexData.h"
#include "Geom.h"
#include "Factories/geom_factories.h"
#include "VertexDataPT.h"
#include "VertexDataP.h"
#include "VertexDataParticles.h"

typedef grynca::TypesPack<
        VertexDataPT, VertexDataP, VertexDataParticles
> VertexDataTypes;

#endif //VERTEXDATA_INCLUDES_H
