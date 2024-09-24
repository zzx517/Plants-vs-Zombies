#pragma once

#include <memory>
#include <string>

#include "rect.hpp"
#include "sdl_init.hpp"
#include "surface.hpp"

namespace zzx {

class WindowDeleter {
public:
    void operator( )(SDL_Window *) noexcept;
};

class Window: public std::unique_ptr<SDL_Window, WindowDeleter> {
private:
    using unique_ptr = std::unique_ptr<SDL_Window, WindowDeleter>;

public:
    class WindowInitError: public InitError {
    public:
        using InitError::InitError;
    };

    using Flags = uint32_t;
    static constexpr RectI CENTERED_HALF
        = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920 / 2, 1080 / 2};

    using unique_ptr::unique_ptr;
    Window(
        const std::string &title, const RectI &pos = CENTERED_HALF,
        Flags flags = SDL_WINDOW_SHOWN);
    Window(const char *title, const RectI &pos = CENTERED_HALF, Flags flags = SDL_WINDOW_SHOWN);
    ~Window( ) noexcept = default;
};

}  // namespace zzx