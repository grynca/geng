#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "GameSystem.h"

namespace grynca {

    // fw
    class Window;

    template <typename GameType>
    class RenderSystem : public GameSystem<GameType> {
    public:
        void init();
        void preUpdate();

        void update(typename GameType::GameEntity& e, float dt);

        virtual RolesMask getNeededRoles() {
            return {GengEntityRoles::erRenderable};
        }

    private:
        Window* window_;
    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
