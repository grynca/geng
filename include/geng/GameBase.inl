#include "GameBase.h"
#include <chrono>
#include <thread>

#define GB_TPL template <typename D>
#define GB_TYPE GameBase<D>

#ifdef WEB
#include <emscripten/emscripten.h>
    static void dispatch_main(void* fp) {
        std::function<void()>* func = (std::function<void()>*)fp;
        (*func)();
    }
#endif

namespace grynca {

    GB_TPL
    inline Timer& GB_TYPE::getTimer() {
        return timer_;
    }

    GB_TPL
    template <typename T>
    inline T& GB_TYPE::getModule() {
        // lazy get
        uint32_t tid = Type<T, GameBase>::getInternalTypeId();
        if (tid >= modules_.size())
            modules_.resize(tid+1, CommonPtr());
        if (!modules_[tid].template getAs<T>())
            modules_[tid] = CommonPtr(new T());

        CommonPtr& ptr = modules_[tid];
        return *(ptr.getAs<T>());
    }

    GB_TPL
    template <typename T>
    inline bool GB_TYPE::containsModule() {
        uint32_t tid = Type<T, GameBase>::getInternalTypeId();
        if (tid >= modules_.size())
            return false;
        CommonPtr& ptr = modules_[tid];
        return ptr.getAs<T>() != NULL;
    }

    GB_TPL
    inline uint32_t GB_TYPE::getFPS()const {
        return fps_;
    }

    GB_TPL
    inline uint32_t GB_TYPE::getUPS()const {
        return ups_;
    }

    GB_TPL
    inline float GB_TYPE::getTargetTicklen()const {
        return target_ticklen_;
    }

    GB_TPL
    inline void GB_TYPE::setUPS(float ups) {
        target_ups_ = ups;
        target_ticklen_ = 1.0f/ups;
    };

    GB_TPL
    inline float GB_TYPE::getLag() {
        return lag_;
    }


    GB_TPL
    inline GB_TYPE::GameBase()
     :  quit_(false), fps_(0), ups_(0), target_ups_(60), target_ticklen_(1.0f/60),
        seconds_timer_(0.0f), update_timer_(0.0f), frame_timer_(0.0f),
        frames_(0), updates_(0)
    {
    }

    GB_TPL
    template <typename EntityTypes>
    void GB_TYPE::initEM(uint32_t initial_ents_reserve) {
        entity_manager_.init<EntityTypes>(initial_ents_reserve, spCount);
    }

    GB_TPL
    inline GB_TYPE::~GameBase() {
        for (size_t i=0; i<modules_.size(); ++i) {
            if (!modules_[i].isNull())
                modules_[i].destroy();
        }
    };

    GB_TPL
    template <typename SystemType>
    inline SystemType& GB_TYPE::addUpdateSystem() {
        return entity_manager_.template addSystem<SystemType>(spUpdate);
    };

    GB_TPL
    template <typename SystemType>
    inline SystemType& GB_TYPE::addRenderSystem() {
        return entity_manager_.template addSystem<SystemType>(spRender);
    };

    GB_TPL
    template <typename SystemType>
    SystemType* GB_TYPE::findUpdateSystem() {
        for (uint32_t i=0; i<entity_manager_.getSystemsPackSize(spUpdate); ++i) {
            SystemType* s = dynamic_cast<SystemType*>(entity_manager_.getSystem(spUpdate, i));
            if (s)
                return s;
        }
        return NULL;
    }

    GB_TPL
    template <typename SystemType>
    SystemType* GB_TYPE::findRenderSystem() {
        for (uint32_t i=0; i<entity_manager_.getSystemsPackSize(spRender); ++i) {
            SystemType* s = dynamic_cast<SystemType*>(entity_manager_.getSystem(spRender, i));
            if (s)
                return s;
        }
        return NULL;
    }

    GB_TPL
    inline void GB_TYPE::start() {
        init();
        seconds_timer_ = update_timer_ = frame_timer_ = lag_ = frames_ = updates_ = 0;
        timer_.reset();

        std::function<void()> main_loop = [this]() {
#ifdef WEB
            if (quit_) {
                emscripten_cancel_main_loop();
                return;
            }
#endif
            float now = timer_.getElapsed();
            float dt_update = now - update_timer_;
            if (dt_update > target_ticklen_) {
                // maximal 1 update during frame to avoid spiral of death (but game can slow down on slow machine)
                getAsDerived_().updateIter_();
                float prev_n = now;
                now = timer_.getElapsed();
                dt_update = now - update_timer_;
            }

            lag_ = dt_update*target_ups_;
            float dt_frame = now - frame_timer_;

            getAsDerived_().renderIter_(dt_frame);
            if (now - seconds_timer_ > 1.0f) {
                seconds_timer_ += 1.0f;
                fps_ = frames_;
                ups_ = updates_;
                frames_ = updates_ = 0;
                tick();
#ifdef PROFILE_BUILD
                std::cout << "lag: " << lag_ << std::endl;
#endif
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
    };

    GB_TPL
    inline void GB_TYPE::quit() {
        quit_ = true;
    };

    GB_TPL
    inline Entity GB_TYPE::createEntity(uint16_t ent_type_id) {
        return getEntitiesManager().createEntity(ent_type_id);
    }

    GB_TPL
    inline EntityManager& GB_TYPE::getEntitiesManager() {
        return entity_manager_;
    };

    GB_TPL
    inline Entity GB_TYPE::getEntity(EntityIndex ent_id) {
        return entity_manager_.getEntity(ent_id);
    };

    GB_TPL
    inline D& GB_TYPE::getAsDerived_() {
        return *(D*)this;
    }

    GB_TPL
    inline void GB_TYPE::updateIter_() {
        update();
        entity_manager_.updateSystemsPack(spUpdate, target_ticklen_);

        updates_++;
        update_timer_ += target_ticklen_;
    };

    GB_TPL
    inline void GB_TYPE::renderIter_(float dt) {
        render();
        entity_manager_.updateSystemsPack(spRender, dt);
        frames_++;
        frame_timer_ += dt;
    };
}

#undef GB_TPL
#undef GB_TYPE