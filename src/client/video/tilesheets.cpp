#include "tilesheets.hpp"

namespace zzx {

Tilesheets::Tilesheets(const Renderer &renderer, const char *file, int l, const Vector2I &shape)
    : Texture {renderer, file}
    , len {l}
    , cols {shape.x}
    , size {Texture::GetSize( ) / shape} { }

Tilesheets::Tilesheets(
    const Renderer &renderer, const std::string &file, int l, const Vector2I &shape)
    : Texture {renderer, file}
    , len {l}
    , cols {shape.x}
    , size {Texture::GetSize( ) / shape} { }

int Tilesheets::GetLength( ) const noexcept {
    return len;
}

int Tilesheets::GetRows( ) const noexcept {
    return len / cols + 1;
}

int Tilesheets::GetCols( ) const noexcept {
    return cols;
}

Vector2I Tilesheets::GetShape( ) const {
    return {GetCols( ), GetRows( )};
}

Vector2I Tilesheets::GetSize( ) const {
    return size;
}

void Tilesheets::GetSize(int &w, int &h) const {
    w = size.x;
    h = size.y;
}

RectI Tilesheets::At(int i) const {
    return {i % cols * size.x, i / cols * size.y, size.x, size.y};
}

void Tilesheets::DrawOn(int i, const Renderer &renderer, const RectI &target) const {
    RectI source = At(i);
    DrawOn(source, renderer, target);
}

void Tilesheets::DrawOn(int i, const Renderer &renderer, const RectF &target) const {
    RectI source = At(i);
    DrawOn(source, renderer, target);
}

void Tilesheets::DrawOn(
    int i, const Renderer &renderer, const RectI &target, Deg rotation, const Vector2I &center,
    Flip flip) const {
    RectI source = At(i);
    DrawOn(source, renderer, target, rotation, center, flip);
}

void Tilesheets::DrawOn(
    int i, const Renderer &renderer, const RectF &target, Deg rotation, const Vector2F &center,
    Flip flip) const {
    RectI source = At(i);
    DrawOn(source, renderer, target, rotation, center, flip);
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

}  // namespace zzx
