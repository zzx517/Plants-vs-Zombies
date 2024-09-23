#include "texture.hpp"

namespace zzx {

template <typename T>
Vector2I _Texture<T>::GetSize( ) const {
    Vector2I size;
    GetSize(&size.x, &size.y);
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
    if (SDL_QueryTexture(static_cast<const T *>(this)->get( ), format, access, w, h)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectI *target) const {
    if (SDL_RenderCopy(renderer.get( ), static_cast<const T *>(this)->get( ), source, target)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectF *target) const {
    if (SDL_RenderCopyF(
            renderer.get( ), static_cast<const T *>(this)->get( ), source, target)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectI *target, Deg rotation,
    const Point2I *center, Flip flip) const {
    if (SDL_RenderCopyEx(
            renderer.get( ), static_cast<const T *>(this)->get( ), source, target, rotation,
            center, flip)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Texture<T>::DrawOn(
    const RectI *source, const Renderer &renderer, const RectF *target, Deg rotation,
    const Point2F *center, Flip flip) const {
    if (SDL_RenderCopyExF(
            renderer.get( ), static_cast<const T *>(this)->get( ), source, target, rotation,
            center, flip)) {
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
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

TextureShared::TextureShared(const Renderer &renderer, const std::string &file)
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

template class ImageOf<Texture>;
template ImageOf<Texture>::ImageOf<const Renderer &, const char *>(
    const Renderer &renderer, const char *file, const RectI &shift);
template ImageOf<Texture>::ImageOf<const Renderer &, const std::string &>(
    const Renderer &renderer, const std::string &file, const RectI &shift);

}  // namespace zzx
