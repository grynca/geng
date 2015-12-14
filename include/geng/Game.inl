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

    template <typename EntSys, typename D>
    template <typename T>
    inline T& Game<EntSys, D>::getModule() {
        // lazy get
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].template getAs<T>())
            modules_[tid] = CommonPtr(new T());

        CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    template <typename EntSys, typename D>
    template <typename T>
    inline bool Game<EntSys, D>::containsModule_() {
        uint32_t tid = Type<T, Game>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        CommonPtr& ptr = modules_[tid];
        return ptr.getAs<T>() != NULL;
    }

    template <typename EntSys, typename D>
    inline D& Game<EntSys, D>::getAsDerived_() {
        return *(D*)this;
    }


    template <typename EntSys, typename D>
    inline void Game<EntSys, D>::start() {
        se_.getUpdateSystemsManager().init();
        se_.getRenderSystemsManager().init();
        init();
        gameLoop_();
    }

    template <typename EntSys, typename D>
    inline uint32_t Game<EntSys, D>::getFPS()const {
        return fps_;
    }

    template <typename EntSys, typename D>
    inline uint32_t Game<EntSys, D>::getUPS()const {
        return ups_;
    }

    template <typename EntSys, typename D>
    inline Game<EntSys, D>::Game(const std::string& name, uint32_t width, uint32_t height)
            : fps_(0), ups_(0), quit_(false)
    {
        GraphicsDomain::setIds();
        getModule<Window>().init(name, width, height);
        getModule<Window>().getEvents().addHandler(SDL_QUIT, [this](SDL_Event& e) {
            quit();
            return false;
        });
    }

    template <typename EntSys, typename D>
    inline Game<EntSys, D>::~Game() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    }

    template <typename EntSys, typename D>
    inline void Game<EntSys, D>::quit() {
        quit_ = true;
    }

    template <typename EntSys, typename D>
    inline void Game<EntSys, D>::gameLoop_() {
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