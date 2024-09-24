#pragma once

#include <stdint.h>

#include <concepts>

namespace zzx {

template <typename _Type = uint32_t>
class Periodic {
public:
    using Type = _Type;

private:
    Type period;

public:
    Periodic(Type period)
        : period {period} { }

    ~Periodic( ) = default;

    inline Type GetPeriod( ) const noexcept { return period; }

    inline void SetPeriod(Type new_period) const noexcept { period = new_period; }
};

template <typename Derived, typename _Type = uint32_t>
// requires requires(Derived c) {
//     { c.GetPeriod( ) } -> std::same_as<_Type>;
// }
class _Counter {
public:
    using Type = _Type;

private:
    Type current;

public:
    _Counter( )
        : current {0} { }

    _Counter(Type start)
        : current {start} { }

    ~_Counter( ) = default;

    Type Get( ) const noexcept { return current; }

    void Set(Type i) noexcept { current = i % static_cast<Derived *>(this)->GetPeriod( ); }

    void Reset( ) noexcept { current = 0; }

    Type Add(bool i = true) {
        if (i) {
            current += 1;
            if (current >= static_cast<Derived *>(this)->GetPeriod( )) {
                current -= static_cast<Derived *>(this)->GetPeriod( );
            }
        }
        return current;
    }

    Type Add(Type i) {
        current += i;
        if (current >= static_cast<Derived *>(this)->GetPeriod( )) {
            if (i >= static_cast<Derived *>(this)->GetPeriod( )) {
                current %= static_cast<Derived *>(this)->GetPeriod( );
            } else {
                current -= static_cast<Derived *>(this)->GetPeriod( );
            }
        }
        return current;
    }
};

template <typename _Type = uint32_t>
class Counter
    : public Periodic<_Type>
    , public _Counter<Periodic<_Type>, _Type> {
public:
    using Type     = _Type;
    using Periodic = Periodic<Type>;

private:
    using Base = _Counter<Periodic, Type>;

public:
    Counter(Type periodic)
        : Periodic(periodic)
        , Base { } { }

    Counter(Type periodic, Type start)
        : Periodic {periodic}
        , Base {start} { }

    ~Counter( ) = default;
};

template <typename Derived, typename _Type = uint32_t>
// requires requires(Derived *ptr) {
//     { ptr->GetAsset( )->GetPeriod( ) } -> std::same_as<_Type>;
// }
class Counting: public _Counter<Derived, _Type> {
public:
    using Type = _Type;

private:
    using Base = _Counter<Derived, Type>;

public:
    Counting( )
        : Base( ) { }

    Counting(Type start)
        : Base(start) { }

    ~Counting( ) = default;

    inline Type GetPeriod( ) const noexcept {
        return static_cast<const Derived *>(this)->GetAsset( )->GetPeriod( );
    }
};

}  // namespace zzx
