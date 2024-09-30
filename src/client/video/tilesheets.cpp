#include "tilesheets.hpp"

namespace zzx {

Tilesheets::Tilesheets(const char *file, const Vector2I &shape)
    : Texture {file}
    , shape {shape}
    , size {Texture::GetSize( ) / shape} { }

Tilesheets::Tilesheets(const std::string &file, const Vector2I &shape)
    : Texture {file}
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

void Tilesheets::DrawOn(int i, const RectI &target) const {
    RectI source = At(i);
    Texture::DrawOn(source, target);
}

void Tilesheets::DrawOn(int i, const RectF &target) const {
    RectI source = At(i);
    Texture::DrawOn(source, target);
}

void Tilesheets::DrawOn(
    int i, const RectI &target, Deg rotation, const Vector2I &center, Flip flip) const {
    RectI source = At(i);
    Texture::DrawOn(source, target, rotation, center, flip);
}

void Tilesheets::DrawOn(
    int i, const RectF &target, Deg rotation, const Vector2F &center, Flip flip) const {
    RectI source = At(i);
    Texture::DrawOn(source, target, rotation, center, flip);
}

Atlas::Atlas(const char *file, const Vector2I &shape, const RectI &shift)
    : Tilesheets {file, shape}
    , SingleDrawingObject {shift} { }

Atlas::Atlas(const std::string &file, const Vector2I &shape, const RectI &shift)
    : Tilesheets {file, shape}
    , SingleDrawingObject {shift} { }

Atlas::Atlas(const char *file, const Vector2I &shape, const Vector2I &shift)
    : Tilesheets {file, shape}
    , SingleDrawingObject {shift} { }

Atlas::Atlas(const std::string &file, const Vector2I &shape, const Vector2I &shift)
    : Tilesheets {file, shape}
    , SingleDrawingObject {shift} { }

}  // namespace zzx
