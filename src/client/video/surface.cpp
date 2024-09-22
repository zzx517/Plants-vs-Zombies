#include "surface.hpp"

namespace zzx {

template <typename T>
Vector2I _Surface<T>::GetSize( ) {
    SDL_Surface *surface = dynamic_cast<T *>(this)->get( );
    return Vector2I {.x = surface->w, .y = surface->h};
}

template <typename T>
void _Surface<T>::SaveJPG(const char *file, int quality) {
    if (IMG_SaveJPG(dynamic_cast<T *>(this)->get( ), file, quality)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Surface<T>::SaveJPG(const std::string &file, int quality) {
    SaveJPG(file.c_str( ), quality);
}

template <typename T>
void _Surface<T>::SavePNG(const char *file) {
    if (IMG_SavePNG(dynamic_cast<T *>(this)->get( ), file)) {
        throw SDL_Error( );
    }
}

template <typename T>
void _Surface<T>::SavePNG(const std::string &file) {
    SavePNG(file.c_str( ));
}

void SurfaceHelper::operator( )(SDL_Surface *s) noexcept {
    SDL_FreeSurface(s);
}

SDL_Surface *SurfaceHelper::Load(const char *file) {
    auto s = IMG_Load(file);
    if (s == nullptr) {
        throw SDL_Error( );
    }
    return s;
}

SDL_Surface *SurfaceHelper::Load(const std::string &file) {
    return SurfaceHelper::Load(file.c_str( ));
}

SDL_Surface *SurfaceHelper::Create(int width, int height, int depth, uint32_t format) {
    auto s = SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, format);
    if (s == nullptr) {
        throw SDL_Error( );
    }
    return s;
}

Surface::Surface(const char *file)
    : unique_ptr(SurfaceHelper::Load(file)) { }

Surface::Surface(const std::string &file)
    : unique_ptr(SurfaceHelper::Load(file)) { }

Surface::Surface(int width, int height, int depth, uint32_t format)
    : unique_ptr(SurfaceHelper::Create(width, height, depth, format)) { }

SurfaceShared::SurfaceShared(const char *file)
    : shared_ptr(SurfaceHelper::Load(file)) { }

SurfaceShared::SurfaceShared(const std::string &file)
    : shared_ptr(SurfaceHelper::Load(file)) { }

SurfaceShared::SurfaceShared(int width, int height, int depth, uint32_t format)
    : shared_ptr(SurfaceHelper::Create(width, height, depth, format)) { }

}  // namespace zzx