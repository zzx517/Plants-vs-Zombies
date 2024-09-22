#include "sdl_init.hpp"

namespace zzx {

SDL::SDL(
    Flags sdl, Flags img, Flags mix, int frequency, uint16_t format, int channels,
    int chunksize) {
    if (SDL_Init(sdl)) {
        throw InitError();
    }
    if (!IMG_Init(img)) {
        throw InitError();
    }
    if (TTF_Init( )) {
        throw InitError();
    }
    if (!Mix_Init(mix)) {
        throw InitError();
    }
    if (Mix_OpenAudio(frequency, format, channels, chunksize)) {
        throw InitError();
    }
}

SDL::~SDL( ) {
    Mix_CloseAudio( );
    Mix_Quit( );
    TTF_Quit( );
    IMG_Quit( );
    SDL_Quit( );
}

const SDL &SDL::Init(
    Flags sdl, Flags img, Flags mix, int frequency, uint16_t format, int channels,
    int chunksize) {
    static SDL single(sdl, img, mix, frequency, format, channels, chunksize);
    return single;
}

}  // namespace zzx