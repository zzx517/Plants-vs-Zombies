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

    _TextureBase( )  = default;
    ~_TextureBase( ) = default;

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

    void DrawOn( ) const { DrawOn(nullptr, nullptr); }

    void DrawOn(const RectI &target) const { DrawOn(nullptr, &target); }

    void DrawOn(const RectF &target) const { DrawOn(nullptr, &target); }

    void DrawOn(const RectI &target, Deg rotation, const Point2I &center, Flip flip) const {
        DrawOn(nullptr, &target, rotation, &center, flip);
    }

    void DrawOn(const RectF &target, Deg rotation, const Point2F &center, Flip flip) const {
        DrawOn(nullptr, &target, rotation, &center, flip);
    }

    void DrawOn(const RectI &source, const RectI &target) const { DrawOn(&source, &target); }

    void DrawOn(const RectI &source, const RectF &target) const { DrawOn(&source, &target); }

    void DrawOn(
        const RectI &source, const RectI &target, Deg rotation, const Point2I &center,
        Flip flip) const {
        DrawOn(&source, &target, rotation, &center, flip);
    }

    void DrawOn(
        const RectI &source, const RectF &target, Deg rotation, const Point2F &center,
        Flip flip) const {
        DrawOn(&source, &target, rotation, &center, flip);
    }

    void DrawOn(const RectI *source, const RectI *target) const {
        if (SDL_RenderCopy(
                Renderer::Get( ).get( ), static_cast<const T *>(this)->get( ), source,
                target)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(const RectI *source, const RectF *target) const {
        if (SDL_RenderCopyF(
                Renderer::Get( ).get( ), static_cast<const T *>(this)->get( ), source,
                target)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(
        const RectI *source, const RectI *target, Deg rotation, const Point2I *center,
        Flip flip) const {
        if (SDL_RenderCopyEx(
                Renderer::Get( ).get( ), static_cast<const T *>(this)->get( ), source, target,
                rotation, center, flip)) {
            throw TextureHelper::RendererDrawError( );
        }
    }

    void DrawOn(
        const RectI *source, const RectF *target, Deg rotation, const Point2F *center,
        Flip flip) const {
        if (SDL_RenderCopyExF(
                Renderer::Get( ).get( ), static_cast<const T *>(this)->get( ), source, target,
                rotation, center, flip)) {
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
    Texture(const char *file);
    Texture(const std::string &file);
    Texture(const Surface &surface);
    Texture(SDL_Surface *surface);
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
    TextureShared(const char *file);
    TextureShared(const std::string &file);
    TextureShared(const Surface &surface);
    TextureShared(SDL_Surface *surface);
    ~TextureShared( ) noexcept                      = default;
    TextureShared(const TextureShared &)            = default;
    TextureShared &operator=(const TextureShared &) = default;
    TextureShared(TextureShared &&)                 = default;
    TextureShared &operator=(TextureShared &&)      = default;
};

class Image
    : public Texture
    , public SingleDrawingObject<Image> {
private:
    using SingleDrawingObject = SingleDrawingObject<Image>;

    Image(const Image &)            = delete;
    Image &operator=(const Image &) = delete;

public:
    Image(const char *file, const RectI &shift);
    Image(const std::string &file, const RectI &shift);
    Image(const char *file, const Vector2I &shift);
    Image(const std::string &file, const Vector2I &shift);
    ~Image( )                  = default;
    Image(Image &&)            = default;
    Image &operator=(Image &&) = default;

    using SingleDrawingObject::DrawOn;
    using Texture::DrawOn;
};

}  // namespace zzx
