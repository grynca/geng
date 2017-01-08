#include "Texture2D.h"
#include "Textures2DManager.h"
#include "types/Index.h"

namespace grynca {

    inline Texture2D::Texture2D(const std::string& name)
     : w_(0), h_(0), d_(0), gl_format_(0), name_(name),  bound_to_(InvalidId())
    {
        GLCall(glGenTextures(1, &gl_handle_));
    }

    inline Texture2D::~Texture2D() {
        GLCall(glDeleteTextures(1, &gl_handle_));
    }

    inline void Texture2D::set(Image::Ref image)
    {
        ASSERT_M(bound_to_ != InvalidId(), "Texture must be bound.");
        set(image.get().getWidth(), image.get().getHeight(), image.get().getDepth(), image.get().getGLFormat(),
            image.get().getDataPtr());
    }

    inline void Texture2D::set(u32 w, u32 h, u32 depth, GLenum format, const void* data) {
        ASSERT_M(bound_to_ != InvalidId(), "Texture must be bound.");
        w_ = w;
        h_ = h;
        d_ = depth;
        gl_format_ = format;

        // set data
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, w_, h_,
                            0, format, GL_UNSIGNED_BYTE, data));

        // set default filters
        setFilters(GL_LINEAR, GL_LINEAR);
        // set default wrapping
        setWrap(GL_REPEAT, GL_REPEAT);
    }

    inline void Texture2D::setFilters(GLenum min, GLenum mag) {
        ASSERT_M(bound_to_ != InvalidId(), "Texture must be bound.");
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
        // set filters
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, min));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag));

    }

    inline void Texture2D::setWrap(GLenum s_wrap, GLenum t_wrap) {
        ASSERT_M(bound_to_ != InvalidId(), "Texture must be bound.");
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
        // set wraps
        GLCall(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap ));
        GLCall(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap ));
    }

    inline Vec2 Texture2D::getSize()const {
        return {(f32)w_, (f32)h_};
    }

    inline u32 Texture2D::getDepth()const {
        return d_;
    }

    inline GLuint Texture2D::getGlHandle()const {
        return gl_handle_;
    }

    inline GLenum Texture2D::getGlFormat()const {
        return gl_format_;
    }

    inline const std::string& Texture2D::getName()const {
        return name_;
    }

    inline void Texture2D::setName(const std::string& name) {
        name_=name;
    }

    inline void Texture2D::bind(u32 slot_id) {
        ASSERT_M(slot_id < getManager().getTextureUnitsCount(),
               "Invalid texture slot id.");
        Index curr_bound_id = getManager().texture_units_[slot_id];
        if ( curr_bound_id != Index::Invalid()) {
            getManager().getItem(curr_bound_id).bound_to_ = InvalidId();
        }
        getManager().texture_units_[slot_id] = getId();
        bound_to_ = slot_id;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot_id));
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
    }
}
