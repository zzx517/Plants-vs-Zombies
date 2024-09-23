#pragma once

#include <memory>
#include <string>

#include "exception.hpp"
#include "image.hpp"
#include "render.hpp"
#include "sdl_init.hpp"

namespace zzx {

template <typename T>
class _Texture {
public:
    using Flip = Renderer::Flip;

    Vector2I GetSize( ) const;
    void     GetSize(int &w, int &h) const;
    uint32_t GetFormat( ) const;
    int      GetAccess( ) const;

    void GetAttributes(uint32_t *format, int *access, int *w, int *h) const;

    void DrawOn(const Renderer &renderer) const;
    void DrawOn(const Renderer &renderer, const RectI &target) const;
    void DrawOn(const Renderer &renderer, const RectF &target) const;
    void DrawOn(
        const Renderer &renderer, const RectI &target, Deg rotation, const Point2I &center,
        Flip flip) const;
    void DrawOn(
        const Renderer &renderer, const RectF &target, Deg rotation, const Point2F &center,
        Flip flip) const;

    void DrawOn(const RectI &source, const Renderer &renderer) const;
    void DrawOn(const RectI &source, const Renderer &renderer, const RectI &target) const;
    void DrawOn(const RectI &source, const Renderer &renderer, const RectF &target) const;
    void DrawOn(
        const RectI &source, const Renderer &renderer, const RectI &target, Deg rotation,
        const Point2I &center, Flip flip) const;
    void DrawOn(
        const RectI &source, const Renderer &renderer, const RectF &target, Deg rotation,
        const Point2F &center, Flip flip) const;

    void DrawOn(const RectI *source, const Renderer &renderer, const RectI *target) const;
    void DrawOn(const RectI *source, const Renderer &renderer, const RectF *target) const;
    void DrawOn(
        const RectI *source, const Renderer &renderer, const RectI *target, Deg rotation,
        const Point2I *center, Flip flip) const;
    void DrawOn(
        const RectI *source, const Renderer &renderer, const RectF *target, Deg rotation,
        const Point2F *center, Flip flip) const;
};

class TextureHelper {
public:
    void                operator( )(SDL_Texture *) noexcept;
    static SDL_Texture *Load(const Renderer &renderer, const char *file);
    static SDL_Texture *Load(const Renderer &renderer, const std::string &file);
};

class Texture
    : public _Texture<Texture>
    , public std::unique_ptr<SDL_Texture, TextureHelper> {
private:
    using unique_ptr = std::unique_ptr<SDL_Texture, TextureHelper>;

    Texture(const Texture &)            = delete;
    Texture &operator=(const Texture &) = delete;

public:
    using unique_ptr::unique_ptr;
    Texture(const Renderer &renderer, const char *file);
    Texture(const Renderer &renderer, const std::string &file);
    ~Texture( ) noexcept           = default;
    Texture(Texture &&)            = default;
    Texture &operator=(Texture &&) = default;
};

class TextureShared
    : public _Texture<Texture>
    , public std::shared_ptr<SDL_Texture> {
private:
    using shared_ptr = std::shared_ptr<SDL_Texture>;

public:
    using shared_ptr::shared_ptr;
    TextureShared(const Renderer &renderer, const char *file);
    TextureShared(const Renderer &renderer, const std::string &file);
    ~TextureShared( ) noexcept = default;
};

using Image = ImageOf<Texture>;

}  // namespace zzx
