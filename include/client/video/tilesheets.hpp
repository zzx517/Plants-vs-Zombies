#pragma once

#include "counter.hpp"
#include "texture.hpp"

namespace zzx {

class Tilesheets: public Texture {
private:
    Vector2I shape, size;

    Tilesheets(const Tilesheets &)            = delete;
    Tilesheets &operator=(const Tilesheets &) = delete;

public:
    Tilesheets(const char *file, const Vector2I &shape);
    Tilesheets(const std::string &file, const Vector2I &shape);
    ~Tilesheets( )                       = default;
    Tilesheets(Tilesheets &&)            = default;
    Tilesheets &operator=(Tilesheets &&) = default;


    int      GetRows( ) const noexcept;
    int      GetCols( ) const noexcept;
    // {.x = cols, .y = rows}
    Vector2I GetShape( ) const;
    Vector2I GetSize( ) const;
    void     GetSize(int &w, int &h) const;

    RectI At(int i) const;

    void DrawOn(int i, const RectI &target) const;
    void DrawOn(int i, const RectF &target) const;
    void DrawOn(
        int i, const RectI &target, Deg rotation, const Vector2I &center, Flip flip) const;
    void DrawOn(
        int i, const RectF &target, Deg rotation, const Vector2F &center, Flip flip) const;
};

// using Atlas = ImageOf<Tilesheets, int>;
class Atlas
    : public Tilesheets
    , public SingleDrawingObject<Atlas, int> {
private:
    using SingleDrawingObject = SingleDrawingObject<Atlas, int>;

    Atlas(const Atlas &)            = delete;
    Atlas &operator=(const Atlas &) = delete;

public:
    using Tilesheets::Flip;

    Atlas(const char *file, const Vector2I &shape, const RectI &shift);
    Atlas(const std::string &file, const Vector2I &shape, const RectI &shift);
    Atlas(const char *file, const Vector2I &shape, const Vector2I &shift);
    Atlas(const std::string &file, const Vector2I &shape, const Vector2I &shift);
    ~Atlas( )                  = default;
    Atlas(Atlas &&)            = default;
    Atlas &operator=(Atlas &&) = default;

    using SingleDrawingObject::DrawOn;
    using Tilesheets::DrawOn;
};

}  // namespace zzx
