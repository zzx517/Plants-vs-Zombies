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

Texture::Texture(const char *file)
    : unique_ptr(TextureHelper::Load(Renderer::Get( ), file)) { }

Texture::Texture(const std::string &file)
    : unique_ptr(TextureHelper::Load(Renderer::Get( ), file)) { }

Texture::Texture(const Surface &surface)
    : unique_ptr(TextureHelper::Create(Renderer::Get( ), surface)) { }

Texture::Texture(SDL_Surface *surface)
    : unique_ptr(TextureHelper::Create(Renderer::Get( ), surface)) { }

TextureShared::TextureShared(const char *file)
    : shared_ptr(TextureHelper::Load(Renderer::Get( ), file), TextureHelper( )) { }

TextureShared::TextureShared(const std::string &file)
    : shared_ptr(TextureHelper::Load(Renderer::Get( ), file), TextureHelper( )) { }

TextureShared::TextureShared(const Surface &surface)
    : shared_ptr(TextureHelper::Create(Renderer::Get( ), surface), TextureHelper( )) { }

TextureShared::TextureShared(SDL_Surface *surface)
    : shared_ptr(TextureHelper::Create(Renderer::Get( ), surface), TextureHelper( )) { }

Image::Image(const char *file, const RectI &shift)
    : Texture {file}
    , SingleDrawingObject {shift} { }

Image::Image(const std::string &file, const RectI &shift)
    : Texture {file}
    , SingleDrawingObject {shift} { }

Image::Image(const char *file, const Vector2I &shift)
    : Texture {file}
    , SingleDrawingObject {shift} { }

Image::Image(const std::string &file, const Vector2I &shift)
    : Texture {file}
    , SingleDrawingObject {shift} { }

}  // namespace zzx
