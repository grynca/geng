#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

namespace grynca {

    // fw
    class Window;

    class RenderSystem : public System
    {
    public:
        struct UpdatePos {
            template <typename T>
            static void f(T& e, Window& window);
        };

        void init(Window& window);

        template <typename T>
        void update(Entity& e, T& t, double /*dt*/);

        virtual RolesMask getNeededRoles();

    private:
        Window* window_;

    };
}


#include "RenderSystem.inl"
#endif //RENDERSYSTEM_H
