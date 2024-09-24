#include "texture.hpp"

namespace zzx {

void TextureHelper::operator( )(SDL_Texture *t) noexcept {
    SDL_DestroyTexture(t);
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const char *file) {
    auto t = IMG_LoadTexture(renderer.get( ), file);
    if (t == nullptr) {
        throw SDL_Error( );
    }
    return t;
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const std::string &file) {
    return Load(renderer, file.c_str( ));
}

Texture::Texture(const Renderer &renderer, const char *file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

Texture::Texture(const Renderer &renderer, const std::string &file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

TextureShared::TextureShared(const Renderer &renderer, const char *file)
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

TextureShared::TextureShared(const Renderer &renderer, const std::string &file)
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

template class ImageOf<Texture>;
template ImageOf<Texture>::ImageOf<const Renderer &, const char *>(
    const Renderer &renderer, const char *file, const RectI &shift);
template ImageOf<Texture>::ImageOf<const Renderer &, const std::string &>(
    const Renderer &renderer, const std::string &file, const RectI &shift);

}  // namespace zzx
