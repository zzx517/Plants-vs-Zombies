#pragma once

#include <SDL2/SDL.h>
#undef main
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <optional>

#include "exception.hpp"

namespace zzx {

class SDL {
public:
    using Flags = uint32_t;

private:
    SDL(Flags sdl, Flags img, Flags mix, int frequency, uint16_t format, int channels,
        int chunksize);
    ~SDL( );
    SDL(const SDL &&)                  = delete;
    const SDL &operator=(const SDL &&) = delete;

public:
    static const SDL &Init(
        Flags sdl = SDL_INIT_EVERYTHING, Flags img = IMG_INIT_PNG | IMG_INIT_JPG,
        Flags mix = MIX_INIT_MP3, int frequency = MIX_DEFAULT_FREQUENCY,
        uint16_t format = MIX_DEFAULT_FORMAT, int channels = MIX_DEFAULT_CHANNELS,
        int chunksize = 4096);
};

}  // namespace zzx
