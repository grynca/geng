#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "maths/Vec2.h"
#include "ViewPort.h"

namespace grynca {
    // fw
    class Textures2DManager;
    class Shaders;
    class Vertices;
    class Renderer2D;


    class Window {
    public:
        Window();
        void init(const std::string& name, uint32_t width, uint32_t height);
        ~Window();

        bool isFullscreen();
        void setFullscreen(bool fs);
        void toggleFullscreen();

        Textures2DManager& getTextures();
        Shaders& getShaders();
        Vertices& getVertices();
        Renderer2D& getRenderer();

        Vec2 getResolution();
        void setResolution(const Vec2& resolution);

        void setClearingColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void clear();
        void render();

        void setVSync(bool value);
        bool getVSync();

        ViewPort& getViewPort();
    private:
        void* sdl_window_;
        void* gl_context_;

        Textures2DManager* textures_;
        Shaders* shaders_;
        Vertices* vertices_;
        Renderer2D* renderer_;
        ViewPort viewport_;
    };

}

#endif //WINDOW_H
