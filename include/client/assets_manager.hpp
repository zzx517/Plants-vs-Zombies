#pragma once

#include <unordered_map>
#include <vector>

#include "animation.hpp"
#include "chunk.hpp"
#include "music.hpp"
#include "render.hpp"
#include "texture.hpp"
#include "tilesheets.hpp"

namespace zzx {

class AssetsManager {
public:
    using Duration = AnimationAsset::Duration;
    using Type     = AnimationAsset::Type;

private:
    std::unordered_map<std::string, Image>          images;
    std::unordered_map<std::string, AnimationAsset> animations;

    AssetsManager( )                                = default;
    AssetsManager(const AssetsManager &)            = delete;
    AssetsManager &operator=(const AssetsManager &) = delete;

public:
    AssetsManager(AssetsManager &&)            = default;
    AssetsManager &operator=(AssetsManager &&) = default;
    ~AssetsManager( )                          = default;

    void   LoadImage(const std::string &name, const std::string &file, const RectI &shift);
    void   LoadImage(const std::string &name, const std::string &file, const Vector2I &shift);
    Image &LoadImage(const std::string &name);

    void LoadAnimationAsset(
        const std::string &name, const std::string &file, const Vector2I &shape,
        const RectI &shift, const Duration &interval, Type length);
    void LoadAnimationAsset(
        const std::string &name, const std::string &file, const Vector2I &shape,
        const Vector2I &shift, const Duration &interval, Type length);
    AnimationAsset &GetAnimationAsset(const std::string &name);

    static AssetsManager &Get( );
};

}  // namespace zzx
