#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "geng/core/GengSystem.h"

namespace grynca {

    // fw
    class Window;
    class CRenderableData;

    class RenderSystem : public GengSystemAll {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erRenderableMask() | GERoles::erTransformMask();
        }

        virtual void init() override;
        virtual void update(f32 dt, EntitiesList& entities) override;
    private:
        Window* window_;
        f32 pred_time_;
    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
