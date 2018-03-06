#include "ControlHelpers.h"

namespace grynca {

    inline Dir2 get2DMotionDir(Events& events, SDL_Scancode left, SDL_Scancode right, SDL_Scancode forward, SDL_Scancode backward) {
        // static
        Dir2 dir;
        dir.accX() -= (int)events.isKeyDown(backward);
        dir.accX() += (int)events.isKeyDown(forward);
        dir.accY() -= (int)events.isKeyDown(left);
        dir.accY() += (int)events.isKeyDown(right);
        if (dir.getX() && dir.getY()) {
            static f32 norm = 1.f/(f32)sqrt(2);
            dir *= norm;
        }
        return dir;
    }

    inline f32 get1DMotionDir(Events& events, SDL_Scancode forward, SDL_Scancode backward) {
        // static
        if (events.isKeyDown(forward)) {
            if (!events.isKeyDown(backward)) {
                return 1;
            }
        }
        else if (events.isKeyDown(backward)) {
            return -1;
        }
        return 0;
    }
}