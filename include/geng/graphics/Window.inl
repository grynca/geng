#include "Window.h"
#include "glinclude.h"
#include "../sdlinclude.h"
#include "graphics_config.h"
#include "Textures2DManager.h"
#include "Vertices.h"
#include "Shaders.h"
#include "Renderer2D.h"
#include "Events.h"
#include "GUI.h"

namespace grynca {

    inline Window::Window()
     : sdl_window_(NULL), gl_context_(NULL), game_(NULL),
       events_(NULL), textures_(NULL), shaders_(NULL),
       vertices_(NULL), renderer_(NULL), gui_(NULL)
    {}

    inline void Window::init(Game& game, const std::string& name, u32 width, u32 height) {
        game_ = &game;
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
            if (SDL_InitSubSystem(SDL_INIT_VIDEO)==-1)
                throw SDL_Exception();
        }
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config::GLVER_MAJOR);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config::GLVER_MINOR);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // create window
        int flags = SDL_WINDOW_OPENGL;
        if (config::START_FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        sdl_window_ = SDL_CreateWindow(name.c_str(),
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       width, height, flags);
        if (!sdl_window_)
            throw SDL_Exception();
        // create gl context
        gl_context_ = SDL_GL_CreateContext((SDL_Window*)sdl_window_);
        if (!gl_context_)
            throw SDL_Exception();

        // init glew
//        if (config::GLVER_MAJOR > 2)
//            glewExperimental = GL_TRUE;
        GLuint err = glewInit();
        if (err!=GLEW_OK)
            throw GLEW_Exception(err);

        /// GL flags
#ifndef WEB
        GLCall(glEnable( GL_POINT_SMOOTH));
        GLCall(glEnable(GL_LINE_SMOOTH));
        GLCall(glHint(GL_LINE_SMOOTH_HINT, GL_NICEST));
        GLCall(glEnable( GL_TEXTURE_2D ));
#endif
        GLCall(glEnable(GL_BLEND));
        GLCall(glDisable(GL_DEPTH_TEST));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        viewport_.setBaseSize({(f32)width, (f32)height});

        events_ = new Events(*this);
        textures_ = new Textures2DManager();
        shaders_ = new Shaders(*this);
        vertices_ = new Vertices(*this);
        renderer_ = new Renderer2D(*this);
        gui_ = new GUI(*this);
    }

    inline Window::~Window() {
        if (gl_context_)
            SDL_GL_DeleteContext((SDL_Window*)gl_context_);
        if (sdl_window_)
            SDL_DestroyWindow((SDL_Window*)sdl_window_);
        if (events_)
            delete events_;
        if (textures_)
            delete textures_;
        if (shaders_)
            delete shaders_;
        if (vertices_)
            delete vertices_;
        if (renderer_)
            delete renderer_;
        if (gui_)
            delete gui_;
    }

    inline bool Window::isFullscreen()const {
        return bool(SDL_GetWindowFlags((SDL_Window*)sdl_window_)&SDL_WINDOW_FULLSCREEN);
    }

    inline void Window::setFullscreen(bool fs) {
        SDL_SetWindowFullscreen((SDL_Window*)sdl_window_, fs?SDL_WINDOW_FULLSCREEN:0);
    }

    inline void Window::toggleFullscreen() {
        setFullscreen(!isFullscreen());
    }

    inline Game& Window::getGame()const {
        return *game_;
    }

    inline Events& Window::getEvents()const {
        return *events_;
    }

    inline Textures2DManager& Window::getTextures()const {
        return *textures_;
    }

    inline Shaders& Window::getShaders()const {
        return *shaders_;
    }

    inline Vertices& Window::getVertices()const {
        return *vertices_;
    }

    inline Renderer2D& Window::getRenderer()const {
        return *renderer_;
    }

    inline GUI& Window::getGUI()const {
        return *gui_;
    }

    inline Vec2 Window::getResolution()const {
        int w, h;
        SDL_GetWindowSize((SDL_Window*)sdl_window_, &w, &h);
        return {(f32)w, (f32)h};
    }

    inline void Window::setResolution(const Vec2& resolution) {
        SDL_SetWindowSize((SDL_Window*)sdl_window_, int(round(resolution.getX())), int(round(resolution.getY())));
    }

    inline void Window::clear() {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    inline void Window::setClearingColor(u8 r, u8 g, u8 b, u8 a) {
        glClearColor((f32)r/255.f, (f32)g/255.f, (f32)b/255.f, (f32)a/255.f);
    }

    inline void Window::render(f32 dt) {
        gui_->update();
        vertices_->update(dt);
        renderer_->render();
        SDL_GL_SwapWindow((SDL_Window*)sdl_window_);        // swap buffers
    }

    inline void Window::setVSync(bool value) {
        SDL_GL_SetSwapInterval(value?1:0);
    }

    inline bool Window::getVSync()const {
        return SDL_GL_GetSwapInterval()==1;
    }

    inline ViewPort& Window::getViewPort() {
        return viewport_;
    }

}
