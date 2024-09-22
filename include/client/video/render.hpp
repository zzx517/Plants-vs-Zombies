#pragma once

#include <memory>

#include "exception.hpp"
#include "rect.hpp"
#include "sdl_init.hpp"
#include "surface.hpp"
#include "window.hpp"

namespace zzx {

using Color = SDL_Color;

class RendererDeleter {
public:
    void operator( )(SDL_Renderer *) noexcept;
};

class Renderer: public std::unique_ptr<SDL_Renderer, RendererDeleter> {
private:
    using unique_ptr = std::unique_ptr<SDL_Renderer, RendererDeleter>;

public:
    using Flip      = SDL_RendererFlip;
    using Flags     = uint32_t;
    using BlendMode = SDL_BlendMode;

    using unique_ptr::unique_ptr;
    Renderer(const Window &, int index = -1, Flags flags = 0);
    Renderer(const Surface &);
    ~Renderer( ) = default;

    void  SetBlendMode(BlendMode blend_mode = SDL_BLENDMODE_BLEND);
    void  SetColor(Color c);
    Color GetColor( ) const;
    void  Clear( );
    void  Clear(Color c);
    void  Present( );
};

}  // namespace zzx
