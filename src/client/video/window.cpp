#include "window.hpp"

namespace zzx {

void WindowDeleter::operator( )(SDL_Window *w) noexcept {
    SDL_DestroyWindow(w);
}

Window::Window(const std::string &title, const RectI &pos, Flags flags)
    : Window(title.c_str( ), pos, flags) { }

Window::Window(const char *title, const RectI &pos, Flags flags)
    : unique_ptr(SDL_CreateWindow(title, pos.x, pos.y, pos.w, pos.h, flags)) {
    if (this->get( ) == nullptr) {
        throw InitError();
    }
}

}  // namespace zzx
