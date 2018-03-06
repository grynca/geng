#ifndef CONTROLHELPERS_H
#define CONTROLHELPERS_H

#include "Events.h"

namespace grynca {

    // presumes +x being forward
    static Dir2 get2DMotionDir(Events& events, SDL_Scancode left, SDL_Scancode right, SDL_Scancode forward, SDL_Scancode backward);
    static f32 get1DMotionDir(Events& events, SDL_Scancode forward, SDL_Scancode backward);
}

#include "ControlHelpers.inl"
#endif //CONTROLHELPERS_H
