#include "music.hpp"

namespace zzx {

void MusicHelper::operator( )(Mix_Music *m) noexcept {
    Mix_FreeMusic(m);
}

Mix_Music *MusicHelper::Load(const char *file) {
    Mix_Music *m = Mix_LoadMUS(file);
    if (m == nullptr) {
        throw LoadFileError( );
    }
    return m;
}

Mix_Music *MusicHelper::Load(const std::string &file) {
    return Load(file.c_str( ));
}

Music::Music(const char *file)
    : unique_ptr(MusicHelper::Load(file)) { }

Music::Music(const std::string &file)
    : unique_ptr(MusicHelper::Load(file)) { }

MusicShared::MusicShared(const char *file)
    : shared_ptr(MusicHelper::Load(file), MusicHelper( )) { }

MusicShared::MusicShared(const std::string &file)
    : shared_ptr(MusicHelper::Load(file), MusicHelper( )) { }

}  // namespace zzx
