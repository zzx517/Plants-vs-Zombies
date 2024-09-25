#pragma once

#include <memory>
#include <string>

#include "exception.hpp"
#include "image.hpp"
#include "render.hpp"
#include "sdl_init.hpp"
#include "surface.hpp"

namespace zzx {

class TextureHelper {
public:
    class QueryError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    class RendererDrawError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    class LoadFileError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    class CreateFromSurfaceError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    void                operator( )(SDL_Texture *) noexcept;
    static SDL_Texture *Load(const Renderer &renderer, const char *file);
    static SDL_Texture *Load(const Renderer &renderer, const std::string &file);
    static SDL_Texture *Create(const Renderer &renderer, const Surface &surface);
    static SDL_Texture *Create(const Renderer &renderer, SDL_Surface *surface);
};

template <typename T>
class _TextureBase {
public:
    using Flip = Renderer::Flip;

    Vector2I GetSize( ) const {
        Vector2I size;
        GetSize(size.x, size.y);
        return size;
    }

    void GetSize(int &w, int &h) const { GetAttributes(nullptr, nullptr, &w, &h); }

    uint32_t GetFormat( ) const {
        uint32_t format;
        GetAttributes(&format, nullptr, nullptr, nullptr);
        return format;
    }

    int GetAccess( ) const {
        int access;
        GetAttributes(nullptr, &access, nullptr, nullptr);
        return access;
    }

    void GetAttributes(uint32_t *format, int *access, int *w, int *h) const {
        if (SDL_QueryTexture(static_cast<const T *>(this)->get( ), format, access, w, h)) {
            throw TextureHelper::QueryError( );
        }
    }

    void DrawOn(const Renderer &renderer) const { DrawOn(nullptr, renderer, nullptr); }

    void DrawOn(const Renderer &renderer, const RectI &target) const {
        DrawOn(nullptr, renderer, &target);
    }

    void DrawOn(const Renderer &renderer, const RectF &target) const {
        DrawOn(nullptr, renderer, &target);
    }

    void DrawOn(
        const Renderer &renderer, const RectI &target, Deg rotation, const Point2I &center,
        Flip flip) const {
        DrawOn(nullptr, renderer, &target, rotation, &center, flip);
    }

    void DrawOn(
        const Renderer &renderer, const RectF &target, Deg rotation, const Point2F &center,
        Flip flip) const {
        DrawOn(nullptr, renderer, &target, rotation, &center, flip);
    }

    void DrawOn(const RectI &source, const Renderer &renderer) const {
        DrawOn(&source, renderer, nullptr);
    }

    void DrawOn(const RectI &source, const Renderer &renderer, const RectI &target) const {
        DrawOn(&source, renderer, &target);
    }

    void DrawOn(const RectI &source, const Renderer &renderer, const RectF &target) const {
        DrawOn(&source, renderer, &target);
    }

    void DrawOn(
        const RectI &source, const Renderer &renderer, const RectI &target, Deg rotation,
        const Point2I &center, Flip flip) const {
        DrawOn(&source, renderer, &target, rotation, &center, flip);
    }

    void DrawOn(
        const RectI &source, const Renderer &renderer, const RectF &target, Deg rotation,
        const Point2F &center, Flip flip) const {
        DrawOn(&source, renderer, &target, rotation, &center, flip);
    }

    void DrawOn(const RectI *source, const Renderer &renderer, const RectI *target) const {
        if (SDL_RenderCopy(
                renderer.get( ), static_cast<const T *>(this)->get( ), source, target)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(const RectI *source, const Renderer &renderer, const RectF *target) const {
        if (SDL_RenderCopyF(
                renderer.get( ), static_cast<const T *>(this)->get( ), source, target)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(
        const RectI *source, const Renderer &renderer, const RectI *target, Deg rotation,
        const Point2I *center, Flip flip) const {
        if (SDL_RenderCopyEx(
                renderer.get( ), static_cast<const T *>(this)->get( ), source, target, rotation,
                center, flip)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(
        const RectI *source, const Renderer &renderer, const RectF *target, Deg rotation,
        const Point2F *center, Flip flip) const {
        if (SDL_RenderCopyExF(
                renderer.get( ), static_cast<const T *>(this)->get( ), source, target, rotation,
                center, flip)) {
            throw TextureHelper::RendererDrawError( );
        }
    }
};

class Texture
    : public _TextureBase<Texture>
    , public std::unique_ptr<SDL_Texture, TextureHelper> {
private:
    using unique_ptr = std::unique_ptr<SDL_Texture, TextureHelper>;

    Texture(const Texture &)            = delete;
    Texture &operator=(const Texture &) = delete;

public:
    using unique_ptr::unique_ptr;
    Texture(const Renderer &renderer, const char *file);
    Texture(const Renderer &renderer, const std::string &file);
    Texture(const Renderer &renderer, const Surface &surface);
    Texture(const Renderer &renderer, SDL_Surface *surface);
    ~Texture( ) noexcept           = default;
    Texture(Texture &&)            = default;
    Texture &operator=(Texture &&) = default;
};

class TextureShared
    : public _TextureBase<TextureShared>
    , public std::shared_ptr<SDL_Texture> {
private:
    using shared_ptr = std::shared_ptr<SDL_Texture>;

public:
    using shared_ptr::shared_ptr;
    TextureShared(const Renderer &renderer, const char *file);
    TextureShared(const Renderer &renderer, const std::string &file);
    TextureShared(const Renderer &renderer, const Surface &surface);
    TextureShared(const Renderer &renderer, SDL_Surface *surface);
    ~TextureShared( ) noexcept                      = default;
    TextureShared(const TextureShared &)            = default;
    TextureShared &operator=(const TextureShared &) = default;
    TextureShared(TextureShared &&)                 = default;
    TextureShared &operator=(TextureShared &&)      = default;
};

using Image = ImageOf<Texture>;

}  // namespace zzx
