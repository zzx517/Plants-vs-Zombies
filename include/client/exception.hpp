#pragma once

#include <SDL2/SDL_error.h>

#include <stdexcept>

namespace zzx {

class SDL_Error: public std::runtime_error {
public:
    using runtime_error::runtime_error;

    SDL_Error( )
        : runtime_error(SDL_GetError( )) { }
};

class InitError: public SDL_Error {
public:
    using SDL_Error::SDL_Error;
};

}  // namespace zzx
