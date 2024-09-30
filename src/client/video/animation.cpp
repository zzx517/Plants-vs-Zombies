#include "animation.hpp"

namespace zzx {

// * AnimationAsset class

AnimationAsset::AnimationAsset(
    const char *file, const Vector2I &shape, const RectI &shift, const Duration &interval,
    Type length)
    : Atlas {file, shape, shift}
    , Interval(interval)
    , Periodic(length) { }

AnimationAsset::AnimationAsset(
    const std::string &file, const Vector2I &shape, const RectI &shift,
    const Duration &interval, Type length)
    : Atlas {file, shape, shift}
    , Interval(interval)
    , Periodic(length) { }

AnimationAsset::AnimationAsset(
    const char *file, const Vector2I &shape, const Vector2I &shift, const Duration &interval,
    Type length)
    : Atlas {file, shape, shift}
    , Interval(interval)
    , Periodic(length) { }

AnimationAsset::AnimationAsset(
    const std::string &file, const Vector2I &shape, const Vector2I &shift,
    const Duration &interval, Type length)
    : Atlas {file, shape, shift}
    , Interval(interval)
    , Periodic(length) { }

Animation::Animation(const AnimationAsset &asset)
    : Counting( )
    , Timming(Time::Get( ), asset.GetInterval( ))
    , asset {&asset} { }

Animation::TimePoint Animation::GetTime( ) const noexcept {
    return Timming::Get( );
}

void Animation::ResetTime( ) noexcept {
    return Timming::Reset( );
}

void Animation::SetTime(const TimePoint &now) noexcept {
    return Timming::Set(now);
}

const AnimationAsset &Animation::GetAsset( ) const {
    return *asset;
}

void Animation::SetAsset(const AnimationAsset &asset) {
    auto time   = GetTime( ) - this->GetInterval( );
    this->asset = &asset;
    SetTime(time);
}

Animation::Type Animation::GetCount( ) const noexcept {
    return Counting::Get( );
}

void Animation::ResetCount( ) noexcept {
    return Counting::Reset( );
}

void Animation::SetCount(Type i) noexcept {
    return Counting::Set(i);
}

void Animation::DrawOn(const Vector2I &pos) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos);
}

void Animation::DrawOn(const Vector2F &pos) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos);
}

void Animation::DrawOn(const Vector2I &pos, float scale) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos, scale);
}

void Animation::DrawOn(const Vector2F &pos, float scale) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos, scale);
}

void Animation::DrawOn(
    const Vector2I &pos, float scale, Deg rotation, const Vector2I &center, Flip flip) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos, scale, rotation, center, flip);
}

void Animation::DrawOn(
    const Vector2F &pos, float scale, Deg rotation, const Vector2F &center, Flip flip) {
    return asset->DrawOn(Add(Test(Time::Get( ))), pos, scale, rotation, center, flip);
}

}  // namespace zzx
