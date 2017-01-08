#ifndef COLLISIONSDEBUGSYSTEM_H
#define COLLISIONSDEBUGSYSTEM_H

namespace grynca {

    // fw
    class CollisionSystem;
    class Window;

    class CollisionsDebugSystem: public GengSystem {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erCollidableMask() | GERoles::erTransformMask();
        }

        CollisionsDebugSystem() : cs_(NULL) {}

        virtual void init() override;

        virtual void updateEntity(Entity& e, f32 dt) override;

    private:
        Window* window_;
        CollisionSystem* cs_;
        Renderer2D::ItemRef rt_;
    };

}

#include "CollisionsDebugSystem.inl"
#endif //COLLISIONSDEBUGSYSTEM_H
