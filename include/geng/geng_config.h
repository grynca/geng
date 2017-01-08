#ifndef GENG_CONFIG_H
#define GENG_CONFIG_H

/// Sysent
#ifndef SYSENT_MAX_ROLES
#   define SYSENT_MAX_ROLES GERoles::end
#endif

#ifndef SYSENT_MAX_FLAGS
#   define SYSENT_MAX_FLAGS GEFlags::end
#endif

#define SYSENT_PIPELINES_CNT 2

/// Geng
#ifndef GENG_NW
#   define GENG_NW 1
#endif

#ifndef GENG_PHYSICS
#   define GENG_PHYSICS 1
#endif

#ifndef GENG_GRAPHICS
#   define GENG_GRAPHICS 1
#endif

#endif //GENG_CONFIG_H
