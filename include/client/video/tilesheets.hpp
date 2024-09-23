#pragma once

#include "texture.hpp"

namespace zzx {

class Tilesheets: public Texture {
private:
    int      len, cols;
    Vector2I size;

    Tilesheets(const Tilesheets &)            = delete;
    Tilesheets &operator=(const Tilesheets &) = delete;

public:
    Tilesheets(const Renderer &renderer, const char *file, int len, const Vector2I &shape);
    Tilesheets(
        const Renderer &renderer, const std::string &file, int len, const Vector2I &shape);
    ~Tilesheets( )                       = default;
    Tilesheets(Tilesheets &&)            = default;
    Tilesheets &operator=(Tilesheets &&) = default;

    using Texture::DrawOn;

    int      GetLength( ) const noexcept;
    int      GetRows( ) const noexcept;
    int      GetCols( ) const noexcept;
    // {.x = cols, .y = rows}
    Vector2I GetShape( ) const;
    Vector2I GetSize( ) const;
    void     GetSize(int &w, int &h) const;

    RectI At(int i) const;

    void DrawOn(int i, const Renderer &renderer, const RectI &target) const;
    void DrawOn(int i, const Renderer &renderer, const RectF &target) const;
    void DrawOn(
        int i, const Renderer &renderer, const RectI &target, Deg rotation,
        const Vector2I &center, Flip flip) const;
    void DrawOn(
        int i, const Renderer &renderer, const RectF &target, Deg rotation,
        const Vector2F &center, Flip flip) const;
};

using Atlas = ImageOf<Tilesheets, int>;

}  // namespace zzx
