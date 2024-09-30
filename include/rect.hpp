#pragma once

#include <SDL2/SDL_rect.h>

#include <concepts>

namespace zzx {

// * Vector2

template <typename T>
struct Vector2 {
    T x, y;

    template <typename O>
    Vector2<O> Cast( ) const {
        return Vector2<O> {static_cast<O>(x), static_cast<O>(y)};
    }

    template <typename O>
    operator Vector2<O>( ) const {
        return Cast<O>( );
    }
};

template <>
struct Vector2<int>: public SDL_Point {
    template <typename O>
    Vector2<O> Cast( ) {
        return Vector2<O> {static_cast<O>(x), static_cast<O>(y)};
    }

    template <typename O>
    operator Vector2<O>( ) {
        return Cast<O>( );
    }
};

template <>
struct Vector2<float>: public SDL_FPoint {
    template <typename O>
    Vector2<O> Cast( ) {
        return Vector2<O> {static_cast<O>(x), static_cast<O>(y)};
    }

    template <typename O>
    operator Vector2<O>( ) {
        return Cast<O>( );
    }
};

using Vector2I = Vector2<int>;
using Vector2F = Vector2<float>;
using Vector2D = Vector2<double>;
using Point2I  = Vector2I;
using Point2F  = Vector2F;
using Point2D  = Vector2D;

template <typename A>
Vector2<A> operator+(const Vector2<A> &a) {
    return a;
}

template <typename A>
Vector2<A> operator-(const Vector2<A> &a) {
    return Vector2<A> {-a.x, -a.y};
}

template <typename A, typename B>
auto operator+(const Vector2<A> &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x + b.x), static_cast<T>(a.y + b.y)};
}

template <typename A, typename B>
auto operator+(const Vector2<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x + b), static_cast<T>(a.y + b)};
}

template <typename A, typename B>
auto operator+(const A &a, const Vector2<B> &b) {
    return b + a;
}

template <typename A>
Vector2<A> &operator+=(Vector2<A> &a, const Vector2<A> &b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename A>
Vector2<A> &operator+=(Vector2<A> &a, const A &b) {
    a.x += b;
    a.y += b;
    return a;
}

template <typename A, typename B>
auto operator-(const Vector2<A> &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x - b.x), static_cast<T>(a.y - b.y)};
}

template <typename A, typename B>
auto operator-(const Vector2<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x - b), static_cast<T>(a.y - b)};
}

template <typename A, typename B>
auto operator-(const A &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a - b.x), static_cast<T>(a - b.y)};
}

template <typename A>
Vector2<A> &operator-=(Vector2<A> &a, const Vector2<A> &b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template <typename A>
Vector2<A> &operator-=(Vector2<A> &a, const A &b) {
    a.x -= b;
    a.y -= b;
    return a;
}

template <typename A, typename B>
auto operator*(const Vector2<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x * b), static_cast<T>(a.y * b)};
}

template <typename A, typename B>
auto operator*(const A &a, const Vector2<B> &b) {
    return b * a;
}

template <typename A>
Vector2<A> &operator*=(Vector2<A> &a, const A &b) {
    a.x *= b;
    a.y *= b;
    return a;
}

template <typename A, typename B>
auto operator/(const Vector2<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x / b), static_cast<T>(a.y / b)};
}

template <typename A, typename B>
auto operator/(const Vector2<A> &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Vector2<T> {static_cast<T>(a.x / b.x), static_cast<T>(a.y / b.y)};
}

template <typename A>
Vector2<A> &operator/=(Vector2<A> &a, const A &b) {
    a.x /= b;
    a.y /= b;
    return a;
}

template <typename A>
Vector2<A> &operator/=(Vector2<A> &a, const Vector2<A> &b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

// * Rect

template <typename T>
struct Rect {
    T x, y, w, h;

    Rect(T x, T y, T w, T h)
        : x {x}
        , y {y}
        , w {w}
        , h {h} { }

    Rect(const Vector2<T> &xy, const Vector2<T> &wh)
        : Rect {xy.x, xy.y, wh.x, wh.y} { }

    template <typename O>
    Rect<O> Cast( ) const {
        return Rect<O> {
            static_cast<O>(x), static_cast<O>(y), static_cast<O>(w), static_cast<O>(h)};
    }

    template <typename O>
    operator Rect<O>( ) const {
        return Cast<O>( );
    }

    template <typename O>
    operator const Vector2<O> &( ) const {
        // FIXME! reinterpret_cast Warning!
        return reinterpret_cast<const Vector2<O> &>(*this);
    }

    template <typename O>
    operator Vector2<O>( ) const {
        return Vector2<O> {x, y};
    }
};

template <>
struct Rect<int>: public SDL_Rect {
    Rect(int x, int y, int w, int h)
        : SDL_Rect {x, y, w, h} { }

    Rect(const Vector2<int> &xy, const Vector2<int> &wh)
        : Rect {xy.x, xy.y, wh.x, wh.y} { }

    template <typename O>
    Rect<O> Cast( ) {
        return Rect<O> {
            static_cast<O>(x), static_cast<O>(y), static_cast<O>(w), static_cast<O>(h)};
    }

    template <typename O>
    operator Rect<O>( ) {
        return Cast<O>( );
    }

    template <typename O>
    operator const Vector2<O> &( ) const {
        // FIXME! reinterpret_cast Warning!
        return reinterpret_cast<const Vector2<O> &>(*this);
    }

    template <typename O>
    operator Vector2<O>( ) const {
        return Vector2<O> {x, y};
    }
};

template <>
struct Rect<float>: public SDL_FRect {
    Rect(float x, float y, float w, float h)
        : SDL_FRect {x, y, w, h} { }

    Rect(const Vector2<float> &xy, const Vector2<float> &wh)
        : Rect {xy.x, xy.y, wh.x, wh.y} { }

    template <typename O>
    Rect<O> Cast( ) {
        return Rect<O> {
            static_cast<O>(x), static_cast<O>(y), static_cast<O>(w), static_cast<O>(h)};
    }

    template <typename O>
    operator Rect<O>( ) {
        return Cast<O>( );
    }

    template <typename O>
    operator const Vector2<O> &( ) const {
        // FIXME! reinterpret_cast Warning!
        return reinterpret_cast<const Vector2<O> &>(*this);
    }

    template <typename O>
    operator Vector2<O>( ) const {
        return Vector2<O> {x, y};
    }
};

using RectI = Rect<int>;
using RectF = Rect<float>;
using RectD = Rect<double>;

template <typename A, typename B>
auto operator+(const Rect<A> &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Rect<T> {
        static_cast<T>(a.x + b.x), static_cast<T>(a.y + b.y), static_cast<T>(a.w),
        static_cast<T>(a.h)};
}

template <typename A, typename B>
auto operator+(const Vector2<A> &a, const Rect<B> &b) {
    return b + a;
}

template <typename A>
Rect<A> &operator+=(Rect<A> &a, const Vector2<A> &b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename A, typename B>
auto operator-(const Rect<A> &a, const Vector2<B> &b) {
    using T = std::common_type_t<A, B>;
    return Rect<T> {
        static_cast<T>(a.x - b.x), static_cast<T>(a.y - b.y), static_cast<T>(a.w),
        static_cast<T>(a.h)};
}

template <typename A>
Rect<A> &operator-=(Rect<A> &a, const Vector2<A> &b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template <typename A, typename B>
auto operator*(const Rect<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Rect<T> {
        static_cast<T>(a.x * b), static_cast<T>(a.y * b), static_cast<T>(a.w * b),
        static_cast<T>(a.h * b)};
}

template <typename A, typename B>
auto operator*(const A &a, const Rect<B> &b) {
    return b * a;
}

template <typename A>
Rect<A> &operator*=(Rect<A> &a, const A &b) {
    a.x *= b;
    a.y *= b;
    a.w *= b;
    a.h *= b;
    return a;
}

template <typename A, typename B>
auto operator/(const Rect<A> &a, const B &b) {
    using T = std::common_type_t<A, B>;
    return Rect<T> {
        static_cast<T>(a.x / b), static_cast<T>(a.y / b), static_cast<T>(a.w / b),
        static_cast<T>(a.h / b)};
}

template <typename A>
Rect<A> &operator/=(Rect<A> &a, const A &b) {
    a.x /= b;
    a.y /= b;
    a.w /= b;
    a.h /= b;
    return a;
}

using Deg = double;

}  // namespace zzx
