#include "chunk.hpp"

namespace zzx {

void ChunkHelper::operator( )(Mix_Chunk *m) noexcept {
    Mix_FreeChunk(m);
}

Mix_Chunk *ChunkHelper::Load(const char *file) {
    Mix_Chunk *m = Mix_LoadWAV(file);
    if (m == nullptr) {
        throw LoadFileError( );
    }
    return m;
}

Mix_Chunk *ChunkHelper::Load(const std::string &file) {
    return Load(file.c_str( ));
}

Chunk::Chunk(const char *file)
    : unique_ptr(ChunkHelper::Load(file)) { }

Chunk::Chunk(const std::string &file)
    : unique_ptr(ChunkHelper::Load(file)) { }

ChunkShared::ChunkShared(const char *file)
    : shared_ptr(ChunkHelper::Load(file), ChunkHelper( )) { }

ChunkShared::ChunkShared(const std::string &file)
    : shared_ptr(ChunkHelper::Load(file), ChunkHelper( )) { }

}  // namespace zzx
