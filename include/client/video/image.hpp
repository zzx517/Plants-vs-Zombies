#pragma once

#include <concepts>

#include "rect.hpp"
#include "render.hpp"
#include "sdl_init.hpp"

namespace zzx {

template <typename Texture, typename... Args>
    requires requires(
        Texture t, Args... args, Renderer renderer, RectI tarI, RectF tarF, Deg rotation,
        Vector2I centerI, Vector2F centerF, Renderer::Flip flip) {
        t.DrawOn(args..., renderer, tarI);
        t.DrawOn(args..., renderer, tarF);
        t.DrawOn(args..., renderer, tarI, rotation, centerI, flip);
        t.DrawOn(args..., renderer, tarF, rotation, centerF, flip);
    }
class ImageOf: public Texture {
public:
    using Flip = Renderer::Flip;

private:
    RectI shift;

    ImageOf(const ImageOf<Texture, Args...> &)                              = delete;
    ImageOf<Texture, Args...> &operator=(const ImageOf<Texture, Args...> &) = delete;

public:
    ImageOf(Texture &&texture, const RectI &shift)
        : Texture(std::move(texture))
        , shift {shift} { }

    template <typename... Init>
    ImageOf(Init... init, const RectI &shift)
        : Texture(init...)
        , shift {shift} { }

    template <typename... I>
    ImageOf<Texture, Args...> Init(I... init, const RectI &shift) {
        return ImageOf<Texture, Args...>(Texture(init...), shift);
    }

    ~ImageOf( )                                                        = default;
    ImageOf(ImageOf<Texture, Args...> &&)                              = default;
    ImageOf<Texture, Args...> &operator=(ImageOf<Texture, Args...> &&) = default;

    void DrawOn(Args... args, const Renderer &renderer, const Vector2I &pos) const {
        Texture::DrawOn(args..., renderer, static_cast<RectI>(shift + pos));
    }

    void DrawOn(Args... args, const Renderer &renderer, const Vector2F &pos) const {
        Texture::DrawOn(args..., renderer, static_cast<RectF>(shift + pos));
    }

    void DrawOn(
        Args... args, const Renderer &renderer, const Vector2I &pos, float scale) const {
        Texture::DrawOn(args..., renderer, static_cast<RectI>(shift * scale + pos));
    }

    void DrawOn(
        Args... args, const Renderer &renderer, const Vector2F &pos, float scale) const {
        Texture::DrawOn(args..., renderer, static_cast<RectF>(shift * scale + pos));
    }

    void DrawOn(
        Args... args, const Renderer &renderer, const Vector2I &pos, float scale, Deg rotation,
        const Vector2I &center, Flip flip) const {
        Texture::DrawOn(
            args..., renderer, static_cast<RectI>(shift * scale) + pos, rotation, center, flip);
    }

    void DrawOn(
        Args... args, const Renderer &renderer, const Vector2F &pos, float scale, Deg rotation,
        const Vector2F &center, Flip flip) const {
        Texture::DrawOn(args..., renderer, shift * scale + pos, rotation, center, flip);
    }
};

}  // namespace zzx
