#pragma once

#include <memory>
#include <string>

#include "exception.hpp"
#include "sdl_init.hpp"

namespace zzx {

class ChunkHelper {
public:
    class PlayError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    class LoadFileError: public SDL_Error {
    public:
        using SDL_Error::SDL_Error;
    };

    void              operator( )(Mix_Chunk *) noexcept;
    static Mix_Chunk *Load(const char *file);
    static Mix_Chunk *Load(const std::string &file);
};

template <typename T>
class _ChunkBase {
public:
    int Play(int channel = -1, int loops = 1) const {
        int res = Mix_PlayChannel(static_cast<const T *>(this)->get( ), loops);
        if (res < 0) {
            throw ChunkHelper::PlayError( );
        }
        return res;
    }

    int Loop(int channel = -1) { return Play(channel, -1); }
};

class Chunk
    : public _ChunkBase<Chunk>
    , public std::unique_ptr<Mix_Chunk, ChunkHelper> {
private:
    using unique_ptr = std::unique_ptr<Mix_Chunk, ChunkHelper>;

    Chunk(const Chunk &)            = delete;
    Chunk &operator=(const Chunk &) = delete;

public:
    using unique_ptr::unique_ptr;
    Chunk(const char *file);
    Chunk(const std::string &file);
    ~Chunk( ) noexcept         = default;
    Chunk(Chunk &&)            = default;
    Chunk &operator=(Chunk &&) = default;
};

class ChunkShared
    : public _ChunkBase<Chunk>
    , public std::shared_ptr<Mix_Chunk> {
private:
    using shared_ptr = std::shared_ptr<Mix_Chunk>;

public:
    using shared_ptr::shared_ptr;
    ChunkShared(const char *file);
    ChunkShared(const std::string &file);
    ~ChunkShared( ) noexcept                    = default;
    ChunkShared(const ChunkShared &)            = default;
    ChunkShared &operator=(const ChunkShared &) = default;
    ChunkShared(ChunkShared &&)                 = default;
    ChunkShared &operator=(ChunkShared &&)      = default;
};
}  // namespace zzx
