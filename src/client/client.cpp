#include "client.hpp"

namespace zzx {

Client &Client::Init( ) {
    static Client c { };
    return c;
}

}  // namespace zzx
