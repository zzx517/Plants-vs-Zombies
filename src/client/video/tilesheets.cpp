#include "tilesheets.hpp"

namespace zzx {

Tilesheets::Tilesheets(
    const Renderer &renderer, const char *file, int length, const Vector2I &shape)
    : Texture {renderer, file}
    , Periodic {length}
    , shape {shape}
    , size {Texture::GetSize( ) / shape} { }

Tilesheets::Tilesheets(
    const Renderer &renderer, const std::string &file, int length, const Vector2I &shape)
    : Texture {renderer, file}
    , Periodic {length}
    , shape {shape}
    , size {Texture::GetSize( ) / shape} { }

int Tilesheets::GetRows( ) const noexcept {
    return shape.y;
}

int Tilesheets::GetCols( ) const noexcept {
    return shape.x;
}

Vector2I Tilesheets::GetShape( ) const {
    return shape;
}

Vector2I Tilesheets::GetSize( ) const {
    return size;
}

void Tilesheets::GetSize(int &w, int &h) const {
    w = size.x;
    h = size.y;
}

RectI Tilesheets::At(int i) const {
    return {i % shape.x * size.x, i / shape.x * size.y, size.x, size.y};
}

void Tilesheets::DrawOn(int i, const Renderer &renderer, const RectI &target) const {
    RectI source = At(i);
    Texture::DrawOn(source, renderer, target);
}

void Tilesheets::DrawOn(int i, const Renderer &renderer, const RectF &target) const {
    RectI source = At(i);
    Texture::DrawOn(source, renderer, target);
}

void Tilesheets::DrawOn(
    int i, const Renderer &renderer, const RectI &target, Deg rotation, const Vector2I &center,
    Flip flip) const {
    RectI source = At(i);
    Texture::DrawOn(source, renderer, target, rotation, center, flip);
}

void Tilesheets::DrawOn(
    int i, const Renderer &renderer, const RectF &target, Deg rotation, const Vector2F &center,
    Flip flip) const {
    RectI source = At(i);
    Texture::DrawOn(source, renderer, target, rotation, center, flip);
}

template class ImageOf<Tilesheets, int>;
template ImageOf<Tilesheets, int>::ImageOf<
    const Renderer &, const char *, int, const Vector2I &>(
    const Renderer &renderer, const char *file, int len, const Vector2I &shape,
    const RectI &shift);
template ImageOf<Tilesheets, int>::ImageOf<
    const Renderer &, const std::string &, int, const Vector2I &>(
    const Renderer &renderer, const std::string &file, int len, const Vector2I &shape,
    const RectI &shift);
template ImageOf<Tilesheets, int>
ImageOf<Tilesheets, int>::Init<const Renderer &, const char *, int, const Vector2I &>(
    const Renderer &renderer, const char *file, int len, const Vector2I &shape,
    const RectI &shift);
template ImageOf<Tilesheets, int>
ImageOf<Tilesheets, int>::Init<const Renderer &, const std::string &, int, const Vector2I &>(
    const Renderer &renderer, const std::string &file, int len, const Vector2I &shape,
    const RectI &shift);

}  // namespace zzx
