#ifndef GENG_H
#define GENG_H

#include "geng/geng_config.h"
#include "base.h"
#include "assets.h"
#include "maths.h"
#include "sysent.h"
#include "geng_enums.h"
#include "geng/Game.h"
#include "geng/core/core_includes.h"
#if GENG_GRAPHICS==1
# include "geng/graphics/graphics_includes.h"
#endif
#if GENG_PHYSICS==1
# include "geng/physics/physics_includes.h"
#endif
#if GENG_NW==1
# include "ggnet.h"
# include "geng/network/network_includes.h"
#endif

#endif //GENG_H
