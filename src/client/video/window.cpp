#include "window.hpp"

namespace zzx {

void WindowHelper::operator( )(SDL_Window *w) noexcept {
    SDL_DestroyWindow(w);
}

SDL_Window *WindowHelper::Create(const char *title, const RectI &pos, Flags flags) {
    SDL_Window *w = SDL_CreateWindow(title, pos.x, pos.y, pos.w, pos.h, flags);
    if (w == nullptr) {
        throw WindowInitError( );
    }
    return w;
}

SDL_Window *WindowHelper::Create(const std::string &title, const RectI &pos, Flags flags) {
    return Create(title.c_str( ), pos, flags);
}

Window::Window(const std::string &title, const RectI &pos, Flags flags)
    : unique_ptr(WindowHelper::Create(title, pos, flags)) { }

Window::Window(const char *title, const RectI &pos, Flags flags)
    : unique_ptr(WindowHelper::Create(title, pos, flags)) { }

Window &Window::Get( ) {
    static Window w(
        "Plants vs. Zombies",
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920 / 2, 1080 / 2}, SDL_WINDOW_SHOWN);
    return w;
}

}  // namespace zzx
