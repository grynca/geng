#ifndef SHADERS_INCLUDE_H
#define SHADERS_INCLUDE_H

#include "Shader.h"
#include "CircleShader.h"
#include "SimpleColorShader.h"
#include "RectBorderShader.h"
#include "SimpleTexturedShader.h"
#include "TextShader.h"
#include "ParticleShader.h"

typedef grynca::TypesPack<
        CircleShader,
        SimpleColorShader,
        RectBorderShader,
        SimpleTexturedShader,
        TextShader,
        ParticleShader
> ShaderTypes;

#endif //SHADERS_INCLUDE_H
