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
     : fps_(0), ups_(0), quit_(false)
    {
        Graphics::setIds();
        getModule<Window>().init(name, width, height);
        getModule<Window>().getEvents().addHandler(SDL_QUIT, [this](SDL_Event& e) {
            quit();
            return false;
        });
        getModule<SystemManager>().getSystem<RenderSystem>().init(getModule<Window>());
    }

    Game::~Game() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    }

    void Game::quit() {
        quit_ = true;
    }

    void Game::gameLoop_() {
        timer_.reset();

        float tick_len = 1.0f / 60.0f;
        float seconds_timer = 0.0f;
        float update_timer = 0.0f;
        uint32_t frames = 0;
        uint32_t updates = 0;

        Window& window = getModule<Window>();
        while (!quit_) {
            window.clear();
            float dt = timer_.getElapsed() - update_timer;
            if (dt > tick_len) {
                window.getEvents().update();
                getModule<SystemManager>().updateAllSystems(getModule<EntityManager>(), tick_len);
                update();
                updates++;
                update_timer += tick_len;
            }
            window.render();
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