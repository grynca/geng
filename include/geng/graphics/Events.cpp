#include "Events.h"
#include "Window.h"

namespace grynca {

    EventFunction::EventFunction(const std::function<bool(SDL_Event&)>& f)
     : f_(f)
    {
        static uint32_t id_giver = 0;
        id_ = id_giver++;
    }

    bool EventFunction::operator()(SDL_Event& e) {
        return f_(e);
    }

    Events::Events(Window& window)
     : mouse_prev_(0), mouse_(0)
    {
        int keys_count;
        keys_ = SDL_GetKeyboardState(&keys_count);
        keys_prev_.resize(size_t(keys_count), 0);
    }

    Window& Events::getWindow()const {
        return *window_;
    }

    void Events::update() {

        std::copy(keys_, keys_+keys_prev_.size(), keys_prev_.begin());
        mouse_prev_ = mouse_;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            EventHandlers& h = handlers_[event.type];
            for (uint32_t i=0; i<h.callbacks_.size(); ++i) {
                if (h.callbacks_[i](event))
                    break;
            }
        }

        int dx = (int)mouse_pos_.getX();
        int dy = (int)mouse_pos_.getY();
        mouse_ = SDL_GetRelativeMouseState(&dx, &dy);
        mouse_delta_.setX(dx);
        mouse_delta_.setY(dy);
        mouse_pos_ += mouse_delta_;
    }

    bool Events::isKeyDown(SDL_Scancode sc)const {
        return keys_[sc];
    }

    bool Events::wasKeyPressed(SDL_Scancode sc)const {
        return keys_[sc] && !keys_prev_[sc];
    }

    bool Events::wasKeyReleased(SDL_Scancode sc)const {
        return !keys_[sc] && keys_prev_[sc];
    }

    bool Events::isButtonDown(MouseButton btn)const {
        return bool(mouse_&SDL_BUTTON(btn));
    }

    bool Events::wasButtonClicked(MouseButton btn)const {
        return bool((mouse_&SDL_BUTTON(btn)) && !(mouse_prev_&SDL_BUTTON(btn)));
    }

    bool Events::wasButtonReleased(MouseButton btn)const {
        return bool(!(mouse_&SDL_BUTTON(btn)) && (mouse_prev_&SDL_BUTTON(btn)));
    }

    const Vec2& Events::getMousePos()const {
        return mouse_pos_ ;
    }

    const Vec2& Events::getMouseDelta()const {
        return mouse_delta_ ;
    }

    uint32_t Events::addHandler(SDL_EventType type, const std::function<bool(SDL_Event&)>& f) {
        handlers_[type].callbacks_.push_back(f);
        return handlers_[type].callbacks_.back().getId();
    }

    void Events::removeHandler(SDL_EventType type, uint32_t id) {
        fast_vector<EventFunction>& cbs = handlers_[type].callbacks_;
        for (uint32_t i=0; i<cbs.size(); ++i) {
            if (cbs[i].getId()==id) {
                handlers_[type].callbacks_.erase(cbs.begin()+i);
                break;
            }
        }
    }

}
