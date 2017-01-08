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

        u32 getId() { return id_; }
    private:
        std::function<bool(SDL_Event&)> f_;
        u32 id_;
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

        u32 addHandler(SDL_EventType type, const std::function<bool(SDL_Event&)>& f);
        void removeHandler(SDL_EventType type, u32 id);
    private:
        Window* window_;

        fast_vector<u8> keys_[2];
        const u8* sdl_keys_;
        u32 keys_current_;

        u32 mouse_prev_;
        u32 mouse_;
        Vec2 mouse_pos_;
        Vec2 mouse_delta_;

        EventHandlers handlers_[SDL_LASTEVENT];
    };

}

#include "Events.inl"
#endif //EVENTS_H
