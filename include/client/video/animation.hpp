#pragma once

#include <chrono>

#include "tilesheets.hpp"
#include "timer.hpp"

namespace zzx {

class AnimationAsset
    : public Atlas
    , public Interval<>
    , public Periodic<int> {
private:
    using Interval = Interval<>;
    using Periodic = Periodic<int>;

public:
    using Type = Periodic::Type;

    AnimationAsset(
        const char *file, const Vector2I &shape, const RectI &shift, const Duration &interval,
        Type length);
    AnimationAsset(
        const std::string &file, const Vector2I &shape, const RectI &shift,
        const Duration &interval, Type length);
    AnimationAsset(
        const char *file, const Vector2I &shape, const Vector2I &shift,
        const Duration &interval, Type length);
    AnimationAsset(
        const std::string &file, const Vector2I &shape, const Vector2I &shift,
        const Duration &interval, Type length);
    ~AnimationAsset( )                                    = default;
    AnimationAsset(AnimationAsset &&) noexcept            = default;
    AnimationAsset &operator=(AnimationAsset &&) noexcept = default;

private:
    AnimationAsset(const AnimationAsset &)            = delete;
    AnimationAsset &operator=(const AnimationAsset &) = delete;
};

class Animation
    : public Counting<Animation, AnimationAsset::Type>
    , public Timming<Animation> {
private:
    using Counting = Counting<Animation, AnimationAsset::Type>;
    using Timming  = Timming<Animation>;

public:
    using Type      = AnimationAsset::Type;
    using Duration  = AnimationAsset::Duration;
    using Clock     = Timming::Clock;
    using TimePoint = Timming::TimePoint;
    using Flip      = AnimationAsset::Flip;

private:
    const AnimationAsset *asset;

public:
    Animation(const AnimationAsset &asset);
    ~Animation( )                               = default;
    Animation(Animation &&) noexcept            = default;
    Animation &operator=(Animation &&) noexcept = default;
    Animation(const Animation &)                = default;
    Animation &operator=(const Animation &)     = default;

    const AnimationAsset &GetAsset( ) const;
    void                  SetAsset(const AnimationAsset &asset);
    using Counting::GetPeriod;
    using Timming::GetInterval;
    Type      GetCount( ) const noexcept;
    void      ResetCount( ) noexcept;
    void      SetCount(Type i) noexcept;
    TimePoint GetTime( ) const noexcept;
    void      ResetTime( ) noexcept;
    void      SetTime(const TimePoint &now) noexcept;

    void DrawOn(const Vector2I &pos);
    void DrawOn(const Vector2F &pos);
    void DrawOn(const Vector2I &pos, float scale);
    void DrawOn(const Vector2F &pos, float scale);
    void DrawOn(
        const Vector2I &pos, float scale, Deg rotation, const Vector2I &center, Flip flip);
    void DrawOn(
        const Vector2F &pos, float scale, Deg rotation, const Vector2F &center, Flip flip);
};

}  // namespace zzx
