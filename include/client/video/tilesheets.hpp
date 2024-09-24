#pragma once

#include "counter.hpp"
#include "texture.hpp"

namespace zzx {

class Tilesheets
    : public Texture
    , public Periodic<int> {
private:
    using Periodic = Periodic<int>;

public:
    using Type = Periodic::Type;

private:
    Vector2I shape, size;

    Tilesheets(const Tilesheets &)            = delete;
    Tilesheets &operator=(const Tilesheets &) = delete;

public:
    Tilesheets(const Renderer &renderer, const char *file, int length, const Vector2I &shape);
    Tilesheets(
        const Renderer &renderer, const std::string &file, int length, const Vector2I &shape);
    ~Tilesheets( )                       = default;
    Tilesheets(Tilesheets &&)            = default;
    Tilesheets &operator=(Tilesheets &&) = default;


    inline int      GetRows( ) const noexcept;
    inline int      GetCols( ) const noexcept;
    // {.x = cols, .y = rows}
    inline Vector2I GetShape( ) const;
    inline Vector2I GetSize( ) const;
    inline void     GetSize(int &w, int &h) const;

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
