#ifndef EVENTS_H
#define EVENTS_H

#include "types/EventsHandler.h"
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

    class Events : public EventsHandler<SDL_Event&> {
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
    private:
        Window* window_;

        fast_vector<u8> keys_[2];
        const u8* sdl_keys_;
        u32 keys_current_;

        u32 mouse_prev_;
        u32 mouse_;
        Vec2 mouse_pos_;
        Vec2 mouse_delta_;
    };

}

#include "Events.inl"
#endif //EVENTS_H
