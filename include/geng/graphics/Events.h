#ifndef EVENTS_H
#define EVENTS_H

#include "maths/Vec2.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <functional>

namespace grynca {

    //fw
    class Window;

    enum MouseButton {
        mbLeft = SDL_BUTTON_LEFT,
        mbMiddle = SDL_BUTTON_MIDDLE,
        mbRight = SDL_BUTTON_RIGHT
    };

    class EventFunction {
    public:
        EventFunction(const std::function<bool(SDL_Event&)>& f);
        bool operator()(SDL_Event& e);

        uint32_t getId() { return id_; }
    private:
        std::function<bool(SDL_Event&)> f_;
        uint32_t id_;
    };

    struct EventHandlers {
    // when callback returns true it prevents further handling
        fast_vector<EventFunction> callbacks_;
    };

    class Events {
    public:
        Events(Window& window);

        Window& getWindow()const;

        void update();

        bool isKeyDown(SDL_Scancode sc)const;
        bool wasKeyPressed(SDL_Scancode sc)const;
        bool wasKeyReleased(SDL_Scancode sc)const;
        bool isButtonDown(MouseButton btn)const;
        bool wasButtonClicked(MouseButton btn)const;
        bool wasButtonReleased(MouseButton btn)const;

        const Vec2& getMousePos()const;
        const Vec2& getMouseDelta()const;

        uint32_t addHandler(SDL_EventType type, const std::function<bool(SDL_Event&)>& f);
        void removeHandler(SDL_EventType type, uint32_t id);
    private:
        Window* window_;

        fast_vector<uint8_t> keys_[2];
        const uint8_t* sdl_keys_;
        uint32_t keys_current_;

        uint32_t mouse_prev_;
        uint32_t mouse_;
        Vec2 mouse_pos_;
        Vec2 mouse_delta_;

        EventHandlers handlers_[SDL_LASTEVENT];
    };

}

#endif //EVENTS_H
