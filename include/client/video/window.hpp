#pragma once

#include <SDL2/SDL_video.h>

#include <memory>
#include <string>

#include "exception.hpp"
#include "rect.hpp"

namespace zzx {

class WindowDeleter {
public:
    void operator( )(SDL_Window *) noexcept;
};

class Window: public std::unique_ptr<SDL_Window, WindowDeleter> {
private:
    using unique_ptr = std::unique_ptr<SDL_Window, WindowDeleter>;

public:
    using Flags = uint32_t;

    using unique_ptr::unique_ptr;
    Window(const std::string &title, const RectI &pos, Flags flags);
    Window(const char *title, const RectI &pos, Flags flags);
    ~Window( ) noexcept = default;
};

}  // namespace zzx