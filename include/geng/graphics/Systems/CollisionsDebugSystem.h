#ifndef COLLISIONSDEBUGSYSTEM_H
#define COLLISIONSDEBUGSYSTEM_H

#include "../Renderables.h"

namespace grynca {

    // fw
    template <typename T> class CollisionSystem;
    class Window;

    template <typename GameType>
    class CollisionsDebugSystem: public GengSystem<GameType> {
    public:
        CollisionsDebugSystem() : cs_(NULL) {}

        void init();

        virtual FlagsMask getTrackedFlags() override {
            return {};
        };

        virtual RolesMask getNeededRoles() override {
            return {GengEntityRoles::erCollidable, GengEntityRoles::erTransform };
        }

        virtual void updateEntity(Entity& e, float dt) override;

    private:
        Window* window_;
        CollisionSystem<GameType>* cs_;
        Renderable rend_;
    };

}

#include "CollisionsDebugSystem.inl"
#endif //COLLISIONSDEBUGSYSTEM_H
