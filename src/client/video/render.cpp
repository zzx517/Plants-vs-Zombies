#include "render.hpp"

namespace zzx {

void RendererHelper::operator( )(SDL_Renderer *r) noexcept {
    SDL_DestroyRenderer(r);
}

SDL_Renderer *RendererHelper::Create(const Window &w, int index, Flags flags) {
    SDL_Renderer *r = SDL_CreateRenderer(w.get( ), index, flags);
    if (r == nullptr) {
        throw RendererInitError( );
    }
    return r;
}

SDL_Renderer *RendererHelper::Create(const Surface &s) {
    SDL_Renderer *r = SDL_CreateSoftwareRenderer(s.get( ));
    if (r == nullptr) {
        throw RendererInitError( );
    }
    return r;
}

Renderer::Renderer(const Window &w, int index, Flags flags)
    : unique_ptr(RendererHelper::Create(w, index, flags)) { }

Renderer::Renderer(const Surface &s)
    : unique_ptr(RendererHelper::Create(s)) { }

void Renderer::SetBlendMode(BlendMode mode) {
    if (SDL_SetRenderDrawBlendMode(get( ), mode)) {
        throw SDL_Error( );
    }
}

void Renderer::SetColor(Color c) {
    if (SDL_SetRenderDrawColor(get( ), c.r, c.g, c.b, c.a)) {
        throw SDL_Error( );
    }
}

Color Renderer::GetColor( ) const {
    Color c;
    if (SDL_GetRenderDrawColor(get( ), &c.r, &c.g, &c.b, &c.a)) {
        throw SDL_Error( );
    }
    return c;
}

void Renderer::Clear( ) {
    if (SDL_RenderClear(get( ))) {
        throw SDL_Error( );
    }
}

void Renderer::Clear(Color c) {
    Color last = GetColor( );
    SetColor(c);
    Clear( );
    SetColor(last);
}

void Renderer::Present( ) {
    SDL_RenderPresent(get( ));
}

Renderer &Renderer::Get( ) {
    static Renderer r(Window::Get( ));
    return r;
}

}  // namespace zzx
