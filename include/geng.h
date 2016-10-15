#ifndef GENG_H
#define GENG_H

#ifndef GENG_NW
# define GENG_NW 1
#endif

#ifndef GENG_PHYSICS
# define GENG_PHYSICS 1
#endif

#include "base.h"
#include "assets.h"
#include "maths.h"
#include "geng/core/core_includes.h"
#include "geng/graphics/graphics_includes.h"
#if GENG_PHYSICS
# include "geng/physics/physics_includes.h"
#endif
#if GENG_NW==1
# include "ggnet.h"
# include "geng/network/network_includes.h"
#endif
#include "geng/Game.h"

#endif //GENG_H
