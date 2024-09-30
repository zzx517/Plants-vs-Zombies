#pragma once

#include "sdl_init.hpp"

namespace zzx {

class Client {
private:
    Client( )                         = default;
    Client(Client &&)                 = delete;
    Client(const Client &)            = delete;
    Client &operator=(Client &&)      = delete;
    Client &operator=(const Client &) = delete;
    ~Client( )                        = default;

public:
    static Client &Init( );
};

}  // namespace zzx
