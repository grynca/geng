#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "../../core/GengSystem.h"

namespace grynca {

    // fw
    class Window;

    template <typename GameType>
    class RenderSystem : public GengSystem<GameType> {
    public:
        void init();

        virtual FlagsMask getTrackedFlags() override {
            return {};
        }

        virtual RolesMask getNeededRoles()  override {
            return {GengEntityRoles::erRenderable};
        }

        virtual void preUpdate() override;
        virtual void updateEntity(Entity& e, float dt) override;
    private:
        void renderEntity_(CRenderables& cr, CTransform& ct, float dt);

        Window* window_;
        float pred_time_;
    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
