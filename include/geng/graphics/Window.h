#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "maths/Vec2.h"
#include "ViewPort.h"

namespace grynca {
    // fw
    class Game;
    class Textures2DManager;
    class Shaders;
    class Vertices;
    class AssetsManager;
    class Renderer2D;
    class Events;
    class GUI;


    class Window {
    public:
        Window();
        void init(Game& game, const std::string& name, u32 width, u32 height);
        ~Window();

        bool isFullscreen()const;
        void setFullscreen(bool fs);
        void toggleFullscreen();

        Game& getGame()const;
        Events& getEvents()const;
        Textures2DManager& getTextures()const;
        Shaders& getShaders()const;
        Vertices& getVertices()const;
        AssetsManager& getAssets()const;
        Renderer2D& getRenderer()const;
        GUI& getGUI()const;

        Vec2 getResolution()const;
        void setResolution(const Vec2& resolution);

        void setClearingColor(u8 r, u8 g, u8 b, u8 a);

        void clear();
        void render(f32 dt);

        void setVSync(bool value);
        bool getVSync()const;

        const ViewPort& getViewPort()const;
        ViewPort& accViewPort();
    private:
        void* sdl_window_;
        void* gl_context_;

        Game* game_;
        Events* events_;
        Textures2DManager* textures_;
        Shaders* shaders_;
        Vertices* vertices_;
        AssetsManager* assets_;
        Renderer2D* renderer_;
        GUI* gui_;

        ViewPort viewport_;
    };

}

#include "Window.inl"
#endif //WINDOW_H
