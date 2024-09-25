#pragma once

#include <memory>
#include <string>

#include "rect.hpp"
#include "sdl_init.hpp"

namespace zzx {

template <typename T>
class _Surface {
public:
    Vector2I GetSize( );

    void SaveJPG(const char *file, int quality);
    void SaveJPG(const std::string &file, int quality);
    void SavePNG(const char *file);
    void SavePNG(const std::string &file);
};

class SurfaceHelper {
public:
    void                operator( )(SDL_Surface *) noexcept;
    static SDL_Surface *Load(const char *file);
    static SDL_Surface *Load(const std::string &file);
    static SDL_Surface *Create(int width, int height, int depth, uint32_t format);
};

class Surface
    : public _Surface<Surface>
    , public std::unique_ptr<SDL_Surface, SurfaceHelper> {
private:
    using unique_ptr = std::unique_ptr<SDL_Surface, SurfaceHelper>;

    Surface(const Surface &)            = delete;
    Surface &operator=(const Surface &) = delete;

public:
    using unique_ptr::unique_ptr;
    Surface(const char *file);
    Surface(const std::string &file);
    Surface(int width, int height, int depth, uint32_t format);
    ~Surface( )                    = default;
    Surface(Surface &&)            = default;
    Surface &operator=(Surface &&) = default;
};

class SurfaceShared
    : public _Surface<SurfaceShared>
    , public std::shared_ptr<SDL_Surface> {
private:
    using shared_ptr = std::shared_ptr<SDL_Surface>;

public:
    using shared_ptr::shared_ptr;
    SurfaceShared(const char *file);
    SurfaceShared(const std::string &file);
    SurfaceShared(int width, int height, int depth, uint32_t format);
    ~SurfaceShared( ) noexcept                      = default;
    SurfaceShared(const SurfaceShared &)            = default;
    SurfaceShared &operator=(const SurfaceShared &) = default;
    SurfaceShared(SurfaceShared &&)                 = default;
    SurfaceShared &operator=(SurfaceShared &&)      = default;
};

}  // namespace zzx
