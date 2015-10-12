#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "sysent.h"

namespace grynca {

    // fw
    class Window;

    class RenderSystem : public GameSystem {
    public:
        template <typename GameType>
        void init(GameType& game);

        void preUpdate();

        template <typename ES>
        void update(Entity<ES>& e, float dt);

        virtual RolesMask getNeededRoles() {
            return {GengEntityRoles::erRenderable};
        }

    private:
        Window* window_;
    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
