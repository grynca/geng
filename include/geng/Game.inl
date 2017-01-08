#include "Game.h"
#include "graphics/Window.h"
#include "graphics/Events.h"
#include <cassert>
#include <stdint.h>

namespace grynca {

    inline Game::Game(const std::string& name, u32 width, u32 height) {
        Window& window = getWindow();
        window.init(*this, name, width, height);
        window.getEvents().addHandler(SDL_QUIT, [this](SDL_Event& e) {
            this->quit();
            return false;
        });
    }

    inline void Game::updateInner_() {
        Window& window = getWindow();
        window.getEvents().update();
        GameBase::updateInner_();
    }

    inline void Game::tickInner_() {
        GameBase::tickInner_();
#ifdef PROFILE_BUILD
        std::cout << getWindow().getVertices().getDebugString(1) << std::endl;
#endif
    }

    inline void Game::renderInner_(f32 dt) {
        Window& window = getWindow();
        window.clear();
        window.getViewPort().updateTransforms();
        GameBase::renderInner_(dt);
    }

    inline Window& Game::getWindow() {
        return this->template getModule<Window>();
    };
}