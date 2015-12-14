#ifndef ERENDERABLES_H
#define ERENDERABLES_H

#include "../graphics/Renderable.h"

namespace grynca {

    class ERenderables : public virtual GengEntity {
    public:
        ERenderables() {
            addRoles({GengEntityRoles::erRenderable});
        }
        Renderables& getRenderables() { return renderables_; }

    private:
        Renderables renderables_;
    };

}

#endif //ERENDERABLES_H
