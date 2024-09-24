#pragma once

#include <chrono>

namespace zzx {

template <typename _Duration = std::chrono::milliseconds>
class Interval {
public:
    using Duration = _Duration;

private:
    Duration interval;

public:
    Interval(const Duration &interval)
        : interval {interval} {};
    ~Interval( ) = default;

    inline Duration GetInterval( ) const noexcept { return interval; }

    inline void SetInterval(Duration new_interval) const noexcept { interval = new_interval; }
};

template <
    typename Derived, typename _Duration = std::chrono::milliseconds,
    typename _Clock = std::chrono::steady_clock>
// requires requires(Derived c) {
//     { c.GetInterval( ) } -> std::same_as<_Duration>;
// }
class _Timer {
public:
    using Duration  = _Duration;
    using Clock     = _Clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

private:
    TimePoint next;

public:
    inline static TimePoint Now( ) {
        return std::chrono::time_point_cast<Duration>(Clock::now( ));
    };

    _Timer(const Duration &interval)
        : next {Now( ) + interval} { }

    _Timer(const TimePoint &now, const Duration &interval)
        : next {now + interval} { }

    ~_Timer( ) = default;

    TimePoint Get( ) const noexcept { return next; }

    void Set(const TimePoint &now) noexcept {
        next = now + static_cast<Derived *>(this)->GetInterval( );
    };

    void Reset( ) noexcept { next = Now( ) + static_cast<Derived *>(this)->GetInterval( ); };

    bool Test(const TimePoint &now) {
        if (now > next) {
            next += static_cast<Derived *>(this)->GetInterval( );
            return true;
        } else {
            return false;
        }
    };
};

template <
    typename _Duration = std::chrono::milliseconds, typename _Clock = std::chrono::steady_clock>
class Timer
    : public Interval<_Duration>
    , public _Timer<Interval<_Duration>, _Duration, _Clock> {
public:
    using Duration  = _Duration;
    using Clock     = _Clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;
    using Interval  = Interval<Duration>;

private:
    using Base = _Timer<Interval, Duration, Clock>;

public:
    Timer(const Duration &interval)
        : Interval {interval}
        , Base {interval} { }

    Timer(const Duration &interval, const TimePoint &now)
        : Interval {interval}
        , Base {now, interval} { }

    ~Timer( ) = default;
};

template <
    typename Derived, typename _Duration = std::chrono::milliseconds,
    typename _Clock = std::chrono::steady_clock>
// requires requires(Derived *ptr) {
//     { ptr->GetAsset( )->GetInterval( ) } -> std::same_as<_Duration>;
// }
class Timming: public _Timer<Derived, _Duration, _Clock> {
public:
    using Duration  = _Duration;
    using Clock     = _Clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

private:
    using _Timer = _Timer<Derived, Duration, Clock>;

public:
    Timming(const Duration &interval)
        : _Timer(interval) { }

    Timming(const TimePoint &now, const Duration &interval)
        : _Timer(now, interval) { }

    ~Timming( ) = default;

    inline Duration GetInterval( ) const noexcept {
        return static_cast<const Derived *>(this)->GetAsset( )->GetInterval( );
    }
};

}  // namespace zzx
