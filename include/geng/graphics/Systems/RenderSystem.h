#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "../../core/GengSystem.h"

namespace grynca {

    // fw
    class Window;

    class RenderSystem : public GengSystem {
    public:
        virtual void init() override;

        virtual RolesMask NeededRoles() override {
            return GERoles::erRenderableMask();
        }

        virtual void preUpdate(f32 dt) override;
        virtual void updateEntity(Entity& e, f32 dt) override;
        virtual void postUpdate(f32 dt) override;
    private:
        void renderEntity_(CRenderables& cr, CTransform& ct);

        Window* window_;
        f32 pred_time_;
    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
