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
    class Events;


    class Window {
    public:
        Window();
        void init(const std::string& name, uint32_t width, uint32_t height);
        ~Window();

        bool isFullscreen()const;
        void setFullscreen(bool fs);
        void toggleFullscreen();

        Events& getEvents()const;
        Textures2DManager& getTextures()const;
        Shaders& getShaders()const;
        Vertices& getVertices()const;
        Renderer2D& getRenderer()const;

        Vec2 getResolution()const;
        void setResolution(const Vec2& resolution);

        void setClearingColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void clear();
        void render();

        void setVSync(bool value);
        bool getVSync()const;

        ViewPort& getViewPort();
    private:
        void* sdl_window_;
        void* gl_context_;

        Events* events_;
        Textures2DManager* textures_;
        Shaders* shaders_;
        Vertices* vertices_;
        Renderer2D* renderer_;
        ViewPort viewport_;
    };

}

#endif //WINDOW_H
