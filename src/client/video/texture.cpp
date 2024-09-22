#include "texture.hpp"

namespace zzx {

template <typename T>
Vector2I _Texture<T>::GetSize( ) const {
    Vector2I size;
    GetSize(&size.w, &size.h);
    return size;
}

template <typename T>
void _Texture<T>::GetSize(int &w, int &h) const {
    GetAttributes(nullptr, nullptr, &w, &h);
}

template <typename T>
uint32_t _Texture<T>::GetFormat( ) const {
    uint32_t format;
    GetAttributes(&format, nullptr, nullptr, nullptr);
    return format;
}

template <typename T>
int _Texture<T>::GetAccess( ) const {
    int access;
    GetAttributes(nullptr, &access, nullptr, nullptr);
    return access;
}

template <typename T>
void _Texture<T>::GetAttributes(uint32_t *format, int *access, int *w, int *h) const {
    if (SDL_QueryTexture(dynamic_cast<T *>(this)->get( ), format, access, w, h)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectI *target) const {
    if (SDL_RenderCopy(renderer.get( ), dynamic_cast<T *>(this)->get( ), source, target)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectF *target) const {
    if (SDL_RenderCopyF(renderer.get( ), dynamic_cast<T *>(this)->get( ), source, target)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectI *target, Deg rotation,
    const Point2I *center, Flip flip) const {
    if (SDL_RenderCopyEx(
            renderer.get( ), dynamic_cast<T *>(this)->get( ), source, target, rotation, center,
            flip)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectF *target, Deg rotation,
    const Point2F *center, Flip flip) const {
    if (SDL_RenderCopyExF(
            renderer.get( ), dynamic_cast<T *>(this)->get( ), source, target, rotation, center,
            flip)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(const Renderer &renderer) const {
    DrawOn(nullptr, renderer, nullptr);
}

template <typename T>
void _Texture<T>::DrawOn(const Renderer &renderer, const RectI &target) const {
    DrawOn(nullptr, renderer, &target);
}

template <typename T>
void _Texture<T>::DrawOn(const Renderer &renderer, const RectF &target) const {
    DrawOn(nullptr, renderer, &target);
}

template <typename T>
void _Texture<T>::DrawOn(
    const Renderer &renderer, const RectI &target, Deg rotation, const Point2I &center,
    Flip flip) const {
    DrawOn(nullptr, renderer, &target, rotation, &center, flip);
}

template <typename T>
void _Texture<T>::DrawOn(
    const Renderer &renderer, const RectF &target, Deg rotation, const Point2F &center,
    Flip flip) const {
    DrawOn(nullptr, renderer, &target, rotation, &center, flip);
}

template <typename T>
void _Texture<T>::DrawOn(const RectI &source, const Renderer &renderer) const {
    DrawOn(&source, renderer, nullptr);
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI &source, const Renderer &renderer, const RectI &target) const {
    DrawOn(&source, renderer, &target);
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI &source, const Renderer &renderer, const RectF &target) const {
    DrawOn(&source, renderer, &target);
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI &source, const Renderer &renderer, const RectI &target, Deg rotation,
    const Point2I &center, Flip flip) const {
    DrawOn(&source, renderer, &target, rotation, &center, flip);
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI &source, const Renderer &renderer, const RectF &target, Deg rotation,
    const Point2F &center, Flip flip) const {
    DrawOn(&source, renderer, &target, rotation, &center, flip);
}

void TextureHelper::operator( )(SDL_Texture *t) noexcept {
    SDL_DestroyTexture(t);
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const char *file) {
    auto t = IMG_LoadTexture(renderer.get( ), file);
    if (t == nullptr) {
        throw SDL_Error( );
    }
    return t;
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const std::string &file) {
    return Load(renderer, file.c_str( ));
}

Texture::Texture(const Renderer &renderer, const char *file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

Texture::Texture(const Renderer &renderer, const std::string &file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

TextureShared::TextureShared(const Renderer &renderer, const char *file)
    : shared_ptr(IMG_LoadTexture(renderer.get( ), file), TextureHelper( )) {
    if (get( ) == nullptr) {
        throw InitError(SDL_GetError( ));
    }
}

TextureShared::TextureShared(const Renderer &renderer, const std::string &file)
    : TextureShared(renderer, file.c_str( )) { }

Image::Image(const Renderer &renderer, const char *file, const RectI &shift)
    : Texture(renderer, file)
    , shift {shift} { }

Image::Image(const Renderer &renderer, const std::string &file, const RectI &shift)
    : Texture(renderer, file)
    , shift {shift} { }

void Image::DrawOn(const Renderer &renderer, const Point2I &pos) const {
    DrawOn(renderer, static_cast<RectI>(shift + pos));
}

void Image::DrawOn(const Renderer &renderer, const Point2F &pos) const {
    DrawOn(renderer, static_cast<RectF>(shift + pos));
}

void Image::DrawOn(const Renderer &renderer, const Point2I &pos, float scale) const {
    DrawOn(renderer, static_cast<RectI>(shift * scale + pos));
}

void Image::DrawOn(const Renderer &renderer, const Point2F &pos, float scale) const {
    DrawOn(renderer, static_cast<RectF>(shift * scale + pos));
}

void Image::DrawOn(
    const Renderer &renderer, const Point2I &pos, float scale, Deg rotation,
    const Point2I &center, Flip flip) const {
    DrawOn(renderer, static_cast<RectI>(shift * scale) + pos, rotation, center, flip);
}

void Image::DrawOn(
    const Renderer &renderer, const Point2F &pos, float scale, Deg rotation,
    const Point2F &center, Flip flip) const {
    DrawOn(renderer, shift * scale + pos, rotation, center, flip);
}

}  // namespace zzx
