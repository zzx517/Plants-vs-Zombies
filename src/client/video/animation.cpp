#include "animation.hpp"

namespace zzx {

// * AnimationAsset class

AnimationAsset::AnimationAsset(
    const Renderer &renderer, const char *file, int length, const Vector2I &shape,
    const RectI &shift, const Duration &interval)
    : Atlas {Atlas::Init<const Renderer &, const char *, int, const Vector2I &>(
          renderer, file, length, shape, shift)}
    , Interval(interval) { }

AnimationAsset::AnimationAsset(
    const Renderer &renderer, const std::string &file, int length, const Vector2I &shape,
    const RectI &shift, const Duration &interval)
    : Atlas {Atlas::Init<const Renderer &, const std::string &, int, const Vector2I &>(
          renderer, file, length, shape, shift)}
    , Interval(interval) { }

Animation::TimePoint Animation::now = Animation::Now( );

Animation::TimePoint Animation::GetNow( ) noexcept {
    return now;
}

void Animation::UpdateNow( ) {
    SetNow(Timming::Now( ));
}

void Animation::SetNow(const TimePoint &now) noexcept {
    Animation::now = now;
}

Animation::Animation(const AnimationAsset &asset)
    : Counting( )
    , Timming(GetNow( ), asset.GetInterval( ))
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

Animation::Type Animation::GetCount( ) const noexcept {
    return Counting::Get( );
}

void Animation::ResetCount( ) noexcept {
    return Counting::Reset( );
}

void Animation::SetCount(Type i) noexcept {
    return Counting::Set(i);
}

void Animation::DrawOn(const Renderer &renderer, const Vector2I &pos) {
    return asset->DrawOn(Add(Test(now)), renderer, pos);
}

void Animation::DrawOn(const Renderer &renderer, const Vector2F &pos) {
    return asset->DrawOn(Add(Test(now)), renderer, pos);
}

void Animation::DrawOn(const Renderer &renderer, const Vector2I &pos, float scale) {
    return asset->DrawOn(Add(Test(now)), renderer, pos, scale);
}

void Animation::DrawOn(const Renderer &renderer, const Vector2F &pos, float scale) {
    return asset->DrawOn(Add(Test(now)), renderer, pos, scale);
}

void Animation::DrawOn(
    const Renderer &renderer, const Vector2I &pos, float scale, Deg rotation,
    const Vector2I &center, Flip flip) {
    return asset->DrawOn(Add(Test(now)), renderer, pos, scale, rotation, center, flip);
}

void Animation::DrawOn(
    const Renderer &renderer, const Vector2F &pos, float scale, Deg rotation,
    const Vector2F &center, Flip flip) {
    return asset->DrawOn(Add(Test(now)), renderer, pos, scale, rotation, center, flip);
}

}  // namespace zzx
