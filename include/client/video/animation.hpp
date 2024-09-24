#pragma once

#include <chrono>

#include "tilesheets.hpp"
#include "timer.hpp"

namespace zzx {

class AnimationAsset
    : public Atlas
    , public Interval<> {
private:
    using Interval = Interval<>;

public:
    using Type = Atlas::Type;

    AnimationAsset(
        const Renderer &renderer, const char *file, int length, const Vector2I &shape,
        const RectI &shift, const Duration &interval);
    AnimationAsset(
        const Renderer &renderer, const std::string &file, int length, const Vector2I &shape,
        const RectI &shift, const Duration &interval);
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
    static TimePoint      now;
    const AnimationAsset *asset;

public:
    static TimePoint GetNow( ) noexcept;
    static void      UpdateNow( );
    static void      SetNow(const TimePoint &now) noexcept;

    Animation(const AnimationAsset &asset);
    ~Animation( )                               = default;
    Animation(Animation &&) noexcept            = default;
    Animation &operator=(Animation &&) noexcept = default;
    Animation(const Animation &)                = default;
    Animation &operator=(const Animation &)     = default;

    inline const AnimationAsset *GetAsset( ) const { return asset; };

    using Counting::GetPeriod;
    using Timming::GetInterval;
    inline Type      GetCount( ) const noexcept;
    inline void      ResetCount( ) noexcept;
    inline void      SetCount(Type i) noexcept;
    inline TimePoint GetTime( ) const noexcept;
    inline void      ResetTime( ) noexcept;
    inline void      SetTime(const TimePoint &now) noexcept;

    void DrawOn(const Renderer &renderer, const Vector2I &pos);
    void DrawOn(const Renderer &renderer, const Vector2F &pos);
    void DrawOn(const Renderer &renderer, const Vector2I &pos, float scale);
    void DrawOn(const Renderer &renderer, const Vector2F &pos, float scale);
    void DrawOn(
        const Renderer &renderer, const Vector2I &pos, float scale, Deg rotation,
        const Vector2I &center, Flip flip);
    void DrawOn(
        const Renderer &renderer, const Vector2F &pos, float scale, Deg rotation,
        const Vector2F &center, Flip flip);
};

}  // namespace zzx
