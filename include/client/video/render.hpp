#pragma once

#include <memory>

#include "exception.hpp"
#include "rect.hpp"
#include "sdl_init.hpp"
#include "surface.hpp"
#include "window.hpp"

namespace zzx {

using Color = SDL_Color;

class RendererHelper {
public:
    using Flip      = SDL_RendererFlip;
    using Flags     = uint32_t;
    using BlendMode = SDL_BlendMode;

    class RendererInitError: public InitError {
    public:
        using InitError::InitError;
    };

    void                 operator( )(SDL_Renderer *) noexcept;
    static SDL_Renderer *Create(const Window &, int index = -1, Flags flags = 0);
    static SDL_Renderer *Create(const Surface &);
};

class Renderer: public std::unique_ptr<SDL_Renderer, RendererHelper> {
private:
    using unique_ptr = std::unique_ptr<SDL_Renderer, RendererHelper>;

public:
    using Flip      = RendererHelper::Flip;
    using Flags     = RendererHelper::Flags;
    using BlendMode = RendererHelper::BlendMode;

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

    static Renderer &Get( );
};

}  // namespace zzx
