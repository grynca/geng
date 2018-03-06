#include "Events.h"
#include "Window.h"

namespace grynca {

    inline Events::Events(Window& window)
     : keys_current_(0), mouse_prev_(0), mouse_(0)
    {
        int keys_count;
        sdl_keys_ = SDL_GetKeyboardState(&keys_count);
        keys_[0].resize(size_t(keys_count), 0);
        keys_[1].resize(size_t(keys_count), 0);
        memcpy(&keys_[keys_current_][0], sdl_keys_, size_t(keys_count));
    }

    inline Window& Events::getWindow()const {
        return *window_;
    }

    inline void Events::update() {
        keys_current_ = 1-keys_current_;
        mouse_prev_ = mouse_;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            emit(event.type, event);
        }

        memcpy(&keys_[keys_current_][0], sdl_keys_, keys_[keys_current_].size());

        int dx = (int)mouse_pos_.getX();
        int dy = (int)mouse_pos_.getY();
        mouse_ = SDL_GetRelativeMouseState(&dx, &dy);
        mouse_delta_.setX(dx);
        mouse_delta_.setY(dy);
        mouse_pos_ += mouse_delta_;
    }

    inline bool Events::isKeyDown(SDL_Scancode sc)const {
        return keys_[keys_current_][sc];
    }

    inline bool Events::wasKeyPressed(SDL_Scancode sc)const {
        return keys_[keys_current_][sc] && !keys_[1-keys_current_][sc];
    }

    inline bool Events::wasKeyReleased(SDL_Scancode sc)const {
        return !keys_[keys_current_][sc] && keys_[1-keys_current_][sc];
    }

    inline bool Events::isButtonDown(MouseButton btn)const {
        return bool(mouse_&SDL_BUTTON(btn));
    }

    inline bool Events::wasButtonClicked(MouseButton btn)const {
        return bool((mouse_&SDL_BUTTON(btn)) && !(mouse_prev_&SDL_BUTTON(btn)));
    }

    inline bool Events::wasButtonReleased(MouseButton btn)const {
        return bool(!(mouse_&SDL_BUTTON(btn)) && (mouse_prev_&SDL_BUTTON(btn)));
    }

    inline const Vec2& Events::getMousePos()const {
        return mouse_pos_ ;
    }

    inline const Vec2& Events::getMouseDelta()const {
        return mouse_delta_ ;
    }

}
