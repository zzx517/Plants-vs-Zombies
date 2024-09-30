#pragma once

#include <concepts>

#include "rect.hpp"
#include "render.hpp"
#include "sdl_init.hpp"

namespace zzx {

template <typename Derived, typename... Args>
class SingleDrawingObject {
public:
    using Flip = Renderer::Flip;

private:
    RectI shift;

    SingleDrawingObject(const SingleDrawingObject<Derived, Args...> &) = delete;
    SingleDrawingObject<Derived, Args...> &operator=(
        const SingleDrawingObject<Derived, Args...> &)
        = delete;

public:
    SingleDrawingObject(const RectI &shift)
        : shift {shift} { }

    SingleDrawingObject(const Vector2I &shift)
        : shift {shift, static_cast<const Derived *>(this)->GetSize( )} { }

    ~SingleDrawingObject( )                                       = default;
    SingleDrawingObject(SingleDrawingObject<Derived, Args...> &&) = default;
    SingleDrawingObject<Derived, Args...> &operator=(SingleDrawingObject<Derived, Args...> &&)
        = default;

    void DrawOn(Args... args, const Vector2I &pos) const {
        static_cast<const Derived *>(this)->DrawOn(args..., static_cast<RectI>(shift + pos));
    }

    void DrawOn(Args... args, const Vector2F &pos) const {
        static_cast<const Derived *>(this)->DrawOn(args..., static_cast<RectF>(shift + pos));
    }

    void DrawOn(Args... args, const Vector2I &pos, float scale) const {
        static_cast<const Derived *>(this)->DrawOn(
            args..., static_cast<RectI>(shift * scale + pos));
    }

    void DrawOn(Args... args, const Vector2F &pos, float scale) const {
        static_cast<const Derived *>(this)->DrawOn(
            args..., static_cast<RectF>(shift * scale + pos));
    }

    void DrawOn(
        Args... args, const Vector2I &pos, float scale, Deg rotation, const Vector2I &center,
        Flip flip) const {
        static_cast<const Derived *>(this)->DrawOn(
            args..., static_cast<RectI>(shift * scale) + pos, rotation, center, flip);
    }

    void DrawOn(
        Args... args, const Vector2F &pos, float scale, Deg rotation, const Vector2F &center,
        Flip flip) const {
        static_cast<const Derived *>(this)->DrawOn(
            args..., shift * scale + pos, rotation, center, flip);
    }
};

}  // namespace zzx
