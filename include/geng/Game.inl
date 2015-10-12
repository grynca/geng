#include "Game.h"
#include "types/Type.h"
#include "graphics/GraphicsDomain.h"
#include "graphics/Window.h"
#include "graphics/Events.h"
#include <cassert>
#include <stdint.h>

#ifdef WEB
#include <emscripten/emscripten.h>
    static void dispatch_main(void* fp) {
        std::function<void()>* func = (std::function<void()>*)fp;
        (*func)();
    }
#endif

namespace grynca {

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    template <typename T>
    inline T& Game<ETs, USTs, RSTs, ERs>::getModule() {
        // lazy get
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].template getAs<T>())
            modules_[tid] = CommonPtr(new T());

        CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    template <typename T>
    inline bool Game<ETs, USTs, RSTs, ERs>::containsModule_() {
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        CommonPtr& ptr = modules_[tid];
        return ptr.getAs<T>() != NULL;
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline void Game<ETs, USTs, RSTs, ERs>::start() {
        init();
        gameLoop_();
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline uint32_t Game<ETs, USTs, RSTs, ERs>::getFPS()const {
        return fps_;
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline uint32_t Game<ETs, USTs, RSTs, ERs>::getUPS()const {
        return ups_;
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline Game<ETs, USTs, RSTs, ERs>::Game(const std::string& name, uint32_t width, uint32_t height)
            : fps_(0), ups_(0), quit_(false)
    {
        GraphicsDomain::setIds();
        getModule<Window>().init(name, width, height);
        getModule<Window>().getEvents().addHandler(SDL_QUIT, [this](SDL_Event& e) {
            quit();
            return false;
        });
        se_.getUpdateSystemsManager().init(*this);
        se_.getRenderSystemsManager().init(*this);
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline Game<ETs, USTs, RSTs, ERs>::~Game() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline void Game<ETs, USTs, RSTs, ERs>::quit() {
        quit_ = true;
    }

    template <typename ETs, typename USTs, typename RSTs, typename ERs>
    inline void Game<ETs, USTs, RSTs, ERs>::gameLoop_() {
        float tick_len = 1.0f / 60.0f;
        float seconds_timer = 0.0f;
        float update_timer = 0.0f;
        float frame_timer = 0.0f;
        uint32_t frames = 0;
        uint32_t updates = 0;

        Window& window = getModule<Window>();

        timer_.reset();
        std::function<void()> main_loop = [&]() {
#ifdef WEB
            if (quit_) {
                emscripten_cancel_main_loop();
                return;
            }
#endif
            window.clear();
            float dt_update = timer_.getElapsed() - update_timer;
            if (dt_update > tick_len) {
                window.getEvents().update();
                update();
                se_.getUpdateSystemsManager().update(tick_len);
                updates++;
                update_timer += tick_len;
            }
            float dt_frame = timer_.getElapsed() - frame_timer;
            render();
            se_.getRenderSystemsManager().update(dt_frame);
            window.render();
            frames++;
            frame_timer += dt_frame;
            if (timer_.getElapsed() - seconds_timer > 1.0f) {
                seconds_timer += 1.0f;
                fps_ = frames;
                ups_ = updates;
                frames = updates = 0;
                tick();
            }
        };
#ifdef WEB
        emscripten_set_main_loop_arg(dispatch_main, &main_loop,
                                     0 /* use browser's framerate */,
                                     1 /* simulate infinite loop */);
#else
        while (!quit_) {
            main_loop();
        }
#endif
    }
}