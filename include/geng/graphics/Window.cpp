#include "Window.h"
#include "glinclude.h"
#include "../sdlinclude.h"
#include "graphics_config.h"
#include "Textures2DManager.h"
#include "Vertices.h"
#include "Shaders.h"
#include "Renderer2D.h"
#include "Events.h"

namespace grynca {

    Window::Window()
     : sdl_window_(NULL), gl_context_(NULL),
       events_(NULL), textures_(NULL), shaders_(NULL), vertices_(NULL), renderer_(NULL)
    {}

    void Window::init(const std::string& name, uint32_t width, uint32_t height) {
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

        viewport_.setBaseSize({(float)width, (float)height});

        events_ = new Events(*this);
        textures_ = new Textures2DManager();
        shaders_ = new Shaders(*this);
        vertices_ = new Vertices(*this);
        renderer_ = new Renderer2D(*this);
    }

    Window::~Window() {
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
    }

    bool Window::isFullscreen()const {
        return bool(SDL_GetWindowFlags((SDL_Window*)sdl_window_)&SDL_WINDOW_FULLSCREEN);
    }

    void Window::setFullscreen(bool fs) {
        SDL_SetWindowFullscreen((SDL_Window*)sdl_window_, fs?SDL_WINDOW_FULLSCREEN:0);
    }

    void Window::toggleFullscreen() {
        setFullscreen(!isFullscreen());
    }

    Events& Window::getEvents()const {
        return *events_;
    }

    Textures2DManager& Window::getTextures()const {
        return *textures_;
    }

    Shaders& Window::getShaders()const {
        return *shaders_;
    }

    Vertices& Window::getVertices()const {
        return *vertices_;
    }

    Renderer2D& Window::getRenderer()const {
        return *renderer_;
    }

    Vec2 Window::getResolution()const {
        int w, h;
        SDL_GetWindowSize((SDL_Window*)sdl_window_, &w, &h);
        return {(float)w, (float)h};
    }

    void Window::setResolution(const Vec2& resolution) {
        SDL_SetWindowSize((SDL_Window*)sdl_window_, int(round(resolution.getX())), int(round(resolution.getY())));
    }

    void Window::clear() {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Window::setClearingColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        glClearColor((float)r/255.f, (float)g/255.f, (float)b/255.f, (float)a/255.f);
    }

    void Window::render() {
        vertices_->syncWithGPU();
        renderer_->render();
        SDL_GL_SwapWindow((SDL_Window*)sdl_window_);        // swap buffers
    }

    void Window::setVSync(bool value) {
        SDL_GL_SetSwapInterval(value?1:0);
    }

    bool Window::getVSync()const {
        return SDL_GL_GetSwapInterval()==1;
    }

    ViewPort& Window::getViewPort() {
        return viewport_;
    }

}
