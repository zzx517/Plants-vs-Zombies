#include "render.hpp"

namespace zzx {

void RendererDeleter::operator( )(SDL_Renderer *r) noexcept {
    SDL_DestroyRenderer(r);
}

Renderer::Renderer(const Window &window, int index, Flags flags)
    : unique_ptr(SDL_CreateRenderer(window.get( ), index, flags)) {
    if (this->get( ) == nullptr) {
        throw RendererInitError();
    }
}

Renderer::Renderer(const Surface &surface)
    : unique_ptr(SDL_CreateSoftwareRenderer(surface.get( ))) {
    if (this->get( ) == nullptr) {
        throw RendererInitError();
    }
}

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

}  // namespace zzx
