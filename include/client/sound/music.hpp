#pragma once

#include <memory>
#include <string>

#include "exception.hpp"
#include "sdl_init.hpp"
#include "timer.hpp"

namespace zzx {

class MusicHelper {
public:
    class PlayError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    class LoadFileError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    void              operator( )(Mix_Music *) noexcept;
    static Mix_Music *Load(const char *file);
    static Mix_Music *Load(const std::string &file);
};

template <typename T>
class _MusicBase {
public:
    void Play(int loops = 1) const {
        if (Mix_PlayMusic(static_cast<const T *>(this)->get( ), loops)) {
            throw MusicHelper::PlayError( );
        }
    }

    void Loop( ) { Play(-1); }

    void FadeIn(const Time<>::Duration &fade_in, int loops = 1) const {
        if (Mix_FadeInMusic(static_cast<const T *>(this)->get( ), loops, fade_in.count( ))) {
            throw MusicHelper::PlayError( );
        }
    }
};

class Music
    : public _MusicBase<Music>
    , public std::unique_ptr<Mix_Music, MusicHelper> {
private:
    using unique_ptr = std::unique_ptr<Mix_Music, MusicHelper>;

    Music(const Music &)            = delete;
    Music &operator=(const Music &) = delete;

public:
    using unique_ptr::unique_ptr;
    Music(const char *file);
    Music(const std::string &file);
    ~Music( ) noexcept         = default;
    Music(Music &&)            = default;
    Music &operator=(Music &&) = default;
};

class MusicShared
    : public _MusicBase<Music>
    , public std::shared_ptr<Mix_Music> {
private:
    using shared_ptr = std::shared_ptr<Mix_Music>;

public:
    using shared_ptr::shared_ptr;
    MusicShared(const char *file);
    MusicShared(const std::string &file);
    ~MusicShared( ) noexcept                    = default;
    MusicShared(const MusicShared &)            = default;
    MusicShared &operator=(const MusicShared &) = default;
    MusicShared(MusicShared &&)                 = default;
    MusicShared &operator=(MusicShared &&)      = default;
};
}  // namespace zzx
