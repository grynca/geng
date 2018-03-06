#ifndef PHYSICS_INCLUDES_H
#define PHYSICS_INCLUDES_H

#include "PhysicsManager.h"
#include "Components/CCollider.h"
#include "Components/CBody.h"
#include "Components/CTreeJoint.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/BoundsSystem.h"
#if GENG_GRAPHICS==1
#   include "Systems/BoundsDebugRenderSystem.h"
#endif
#include "physics_utils.h"
#include "motor_utils.h"
#include "physics_entities.h"

#endif //PHYSICS_INCLUDES_H
