#ifndef SHADERS_H
#define SHADERS_H

#include "types/Manager.h"

namespace grynca {

    // fw
    class Shader;
    class Window;

    class Shaders : public ManagerSingletons<Shader> {
    public:
        Shaders(Window& w);

        Shader* getBoundShader();
        Window& getWindow();

        std::string getTypesDebugString()const;
    private:
        friend class Shader;

        Window* window_;
        u32 bound_id_;
    };
}

#include "Shaders.inl"
#endif //SHADERS_H
