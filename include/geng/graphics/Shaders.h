#ifndef SHADERS_H
#define SHADERS_H

#include "types/Manager.h"

namespace grynca {

    // fw
    class Shader;
    class Window;

    class Shaders : public ManagerSingletons<Shaders, Shader> {
    public:
        Shaders(Window& w);

        Shader* getBoundShader();
        Window& getWindow();
    private:
        friend class Shader;

        Window* window_;
        uint32_t bound_id_;
    };
}

#include "Shaders.inl"
#endif //SHADERS_H
