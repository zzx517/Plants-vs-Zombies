#include "texture.hpp"

namespace zzx {

void TextureHelper::operator( )(SDL_Texture *t) noexcept {
    SDL_DestroyTexture(t);
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const char *file) {
    SDL_Texture *t = IMG_LoadTexture(renderer.get( ), file);
    if (t == nullptr) {
        throw LoadFileError( );
    }
    return t;
}

SDL_Texture *TextureHelper::Load(const Renderer &renderer, const std::string &file) {
    return Load(renderer, file.c_str( ));
}

SDL_Texture *TextureHelper::Create(const Renderer &renderer, const Surface &surface) {
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer.get( ), surface.get( ));
    if (t == nullptr) {
        throw CreateFromSurfaceError( );
    }
    return t;
}

SDL_Texture *TextureHelper::Create(const Renderer &renderer, SDL_Surface *surface) {
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer.get( ), surface);
    SDL_FreeSurface(surface);
    if (t == nullptr) {
        throw CreateFromSurfaceError( );
    }
    return t;
}

Texture::Texture(const Renderer &renderer, const char *file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

Texture::Texture(const Renderer &renderer, const std::string &file)
    : unique_ptr(TextureHelper::Load(renderer, file)) { }

Texture::Texture(const Renderer &renderer, const Surface &surface)
    : unique_ptr(TextureHelper::Create(renderer, surface)) { }

Texture::Texture(const Renderer &renderer, SDL_Surface *surface)
    : unique_ptr(TextureHelper::Create(renderer, surface)) { }

TextureShared::TextureShared(const Renderer &renderer, const char *file)
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

TextureShared::TextureShared(const Renderer &renderer, const std::string &file)
    : shared_ptr(TextureHelper::Load(renderer, file), TextureHelper( )) { }

TextureShared::TextureShared(const Renderer &renderer, const Surface &surface)
    : shared_ptr(TextureHelper::Create(renderer, surface), TextureHelper( )) { }

TextureShared::TextureShared(const Renderer &renderer, SDL_Surface *surface)
    : shared_ptr(TextureHelper::Create(renderer, surface), TextureHelper( )) { }

template class ImageOf<Texture>;
template ImageOf<Texture>::ImageOf<const Renderer &, const char *>(
    const Renderer &renderer, const char *file, const RectI &shift);
template ImageOf<Texture>::ImageOf<const Renderer &, const std::string &>(
    const Renderer &renderer, const std::string &file, const RectI &shift);

}  // namespace zzx
