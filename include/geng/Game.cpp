#include "Game.h"
#include "graphics/Window.h"
#include "sysent.h"
#include <cassert>
#include <stdint.h>

namespace grynca {

    void Game::start() {
        init();
        gameLoop_();
    }

    uint32_t Game::getFPS()const {
        return fps_;
    }

    uint32_t Game::getUPS()const {
        return ups_;
    }

    Game::Game(const std::string& name, uint32_t width, uint32_t height)
     : fps_(0), ups_(0)
    {
        Graphics::setIds();
        getModule<Window>().init(name, width, height);
        getModule<SystemManager>().getSystem<RenderSystem>().init(getModule<Window>());
    }

    Game::~Game() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    }

    void Game::gameLoop_() {
        timer_.reset();

        float tick_len = 1.0f / 60.0f;
        float seconds_timer = 0.0f;
        float update_timer = 0.0f;
        uint32_t frames = 0;
        uint32_t updates = 0;

        while (true) {
            // process input
            SDL_Event event;
            // internal handlers first
            while (SDL_PollEvent(&event)) {}

            getModule<Window>().clear();
            float dt = timer_.getElapsed() - update_timer;
            if (dt > tick_len) {
                //m_Window->UpdateInput();
                getModule<SystemManager>().updateAllSystems(getModule<EntityManager>(), tick_len);
                update();
                updates++;
                update_timer += tick_len;
            }
            getModule<Window>().render();
            frames++;
            if (timer_.getElapsed() - seconds_timer > 1.0f) {
                seconds_timer += 1.0f;
                fps_ = frames;
                ups_ = updates;
                frames = updates = 0;
                tick();
            }
        }
    }
}