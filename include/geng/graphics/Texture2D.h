#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "glinclude.h"
#include "types/Manager.h"
#include "maths/Vec2.h"
#include "assets/Image.h"
#include <unordered_map>

namespace grynca {

    // fw
    class Textures2DManager;

    class Texture2D : public ManagedItem<Textures2DManager> {
    public:
        Texture2D(const ustring& name = "");        // unbound uninitialized texture
        ~Texture2D();

        void set(Image::Ref image);
        void set(u32 w, u32 h, u32 depth, GLenum format, const void* data);

        void setFilters(GLenum min, GLenum mag);
        void setWrap(GLenum s_wrap, GLenum t_wrap);

        Vec2 getSize()const;
        u32 getDepth()const;    // bytes per pixel
        GLuint getGlHandle()const;
        GLenum getGlFormat()const;

        const ustring& getName()const;
        void setName(const ustring& name);

        void bind(u32 slot_id);

        // TODO: some functions for simpler reading&writing (e.g mapping/unmapping, PBOs ... )
    private:
        u32 w_, h_, d_;
        GLenum gl_format_;
        GLuint gl_handle_;
        ustring name_;
        u32 bound_to_;
    };
}

#include "Texture2D.inl"
#endif //TEXTURE2D_H
