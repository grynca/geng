#include "Game.h"
#include "geng/graphics/Renderables.h"
#include "graphics/Window.h"
#include "graphics/Events.h"
#include <cassert>
#include <stdint.h>

#define GAME_TPL template <typename D>
#define GAME_TYPE Game<D>

namespace grynca {

    GAME_TPL
    inline GAME_TYPE::Game(const std::string& name, uint32_t width, uint32_t height) {
        Window& window = getWindow_();
        window.init(name, width, height);
        window.getEvents().addHandler(SDL_QUIT, [this](SDL_Event& e) {
            this->quit();
            return false;
        });

        printRenderableSize();
    }

    GAME_TPL
    inline void GAME_TYPE::updateIter_() {
        Window& window = getWindow_();
        window.getEvents().update();
        GameBase<D>::updateIter_();
    }
    GAME_TPL
    inline void GAME_TYPE::renderIter_(float dt) {
        Window& window = getWindow_();
        window.clear();
        window.getViewPort().updateTransforms();
        GameBase<D>::renderIter_(dt);
        window.render();
    }

    GAME_TPL
    inline Window& GAME_TYPE::getWindow_() {
        return this->template getModule<Window>();
    };
}

#undef GAME_TPL
#undef GAME_TYPE