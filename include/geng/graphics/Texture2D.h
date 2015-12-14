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
        Texture2D(const std::string& name = "");        // unbound uninitialized texture
        ~Texture2D();

        void set(Image::Ref image);
        void set(uint32_t w, uint32_t h, uint32_t depth, GLenum format, const void* data);

        void setFilters(GLenum min, GLenum mag);
        void setWrap(GLenum s_wrap, GLenum t_wrap);

        Vec2 getSize()const;
        uint32_t getDepth()const;    // bytes per pixel
        GLuint getGlHandle()const;
        GLenum getGlFormat()const;

        const std::string& getName()const;
        void setName(const std::string& name);

        void bind(uint32_t slot_id);

        // TODO: some functions for simpler reading&writing (e.g mapping/unmapping, PBOs ... )
    private:
        uint32_t w_, h_, d_;
        GLenum gl_format_;
        GLuint gl_handle_;
        std::string name_;
        uint32_t bound_to_;
    };
}

#endif //TEXTURE2D_H
