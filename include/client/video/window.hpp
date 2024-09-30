#pragma once

#include <memory>
#include <string>

#include "rect.hpp"
#include "sdl_init.hpp"
#include "surface.hpp"

namespace zzx {

class WindowHelper {
public:
    using Flags = uint32_t;

    class WindowInitError: public InitError {
    public:
        using InitError::InitError;
    };

    void               operator( )(SDL_Window *) noexcept;
    static SDL_Window *Create(const char *title, const RectI &pos, Flags flags);
    static SDL_Window *Create(const std::string &title, const RectI &pos, Flags flags);
};

class Window: public std::unique_ptr<SDL_Window, WindowHelper> {
private:
    using unique_ptr = std::unique_ptr<SDL_Window, WindowHelper>;

public:
    using Flags = WindowHelper::Flags;

    using unique_ptr::unique_ptr;
    Window(const std::string &title, const RectI &pos, Flags flags);
    Window(const char *title, const RectI &pos, Flags flags);
    ~Window( ) noexcept = default;

    static Window &Get( );
};

}  // namespace zzx