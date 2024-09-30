#include "assets_manager.hpp"

namespace zzx {

void AssetsManager::LoadImage(
    const std::string &name, const std::string &file, const RectI &shift) {
    images.insert({
        name, Image {file, shift}
    });
}

void AssetsManager::LoadImage(
    const std::string &name, const std::string &file, const Vector2I &shift) {
    images.insert({
        name, Image {file, shift}
    });
}

Image &AssetsManager::LoadImage(const std::string &name) {
    return images.at(name);
}

void AssetsManager::LoadAnimationAsset(
    const std::string &name, const std::string &file, const Vector2I &shape, const RectI &shift,
    const Duration &interval, Type length) {
    animations.insert({
        name, AnimationAsset {file, shape, shift, interval, length}
    });
}

void AssetsManager::LoadAnimationAsset(
    const std::string &name, const std::string &file, const Vector2I &shape,
    const Vector2I &shift, const Duration &interval, Type length) {
    animations.insert({
        name, AnimationAsset {file, shape, shift, interval, length}
    });
}

AnimationAsset &AssetsManager::GetAnimationAsset(const std::string &name) {
    return animations.at(name);
}

AssetsManager &AssetsManager::Get( ) {
    static AssetsManager m { };
    return m;
}

}  // namespace zzx
