#ifndef SDLINCLUDE_H
#define SDLINCLUDE_H

#include "types/Exception.h"
#include <SDL.h>

namespace grynca {
    struct SDL_Exception : public Exception
    {
        SDL_Exception() throw()
                : Exception(std::string("SDL : ") + SDL_GetError())
        {}

        SDL_Exception(const char * text) throw()
                : Exception(std::string("SDL : ") + text + SDL_GetError())
        {}
    };

}

#endif //SDLINCLUDE_H
