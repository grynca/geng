#include "Texture2D.h"
#include "Textures2DManager.h"

namespace grynca {

    Texture2D::Texture2D(const std::string& name)
     : w_(0), h_(0), d_(0), gl_format_(0), name_(name),  bound_to_(UNBOUND_ID)
    {
        GLCall(glGenTextures(1, &gl_handle_));
    }

    Texture2D::~Texture2D() {
        GLCall(glDeleteTextures(1, &gl_handle_));
    }

    void Texture2D::set(Image::Ref image)
    {
        ASSERT(bound_to_ != UNBOUND_ID, "Texture must be bound.");
        set(image.get().getWidth(), image.get().getHeight(), image.get().getDepth(), image.get().getGLFormat(),
            image.get().getDataPtr());
    }

    void Texture2D::set(uint32_t w, uint32_t h, uint32_t depth, GLenum format, const void* data) {
        ASSERT(bound_to_ != UNBOUND_ID, "Texture must be bound.");
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

    void Texture2D::setFilters(GLenum min, GLenum mag) {
        ASSERT(bound_to_ != UNBOUND_ID, "Texture must be bound.");
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
        // set filters
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, min));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag));

    }

    void Texture2D::setWrap(GLenum s_wrap, GLenum t_wrap) {
        ASSERT(bound_to_ != UNBOUND_ID, "Texture must be bound.");
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
        // set wraps
        GLCall(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap ));
        GLCall(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap ));
    }

    Vec2 Texture2D::getSize()const {
        return {(float)w_, (float)h_};
    }

    uint32_t Texture2D::getDepth()const {
        return d_;
    }

    GLuint Texture2D::getGlHandle()const {
        return gl_handle_;
    }

    GLenum Texture2D::getGlFormat()const {
        return gl_format_;
    }

    const std::string& Texture2D::getName()const {
        return name_;
    }

    void Texture2D::setName(const std::string& name) {
        name_=name;
    }

    void Texture2D::bind(uint32_t slot_id) {
        ASSERT(slot_id < getManager().getTextureUnitsCount(),
               "Invalid texture slot id.");
        uint32_t curr_bound_id = getManager().texture_units_[slot_id];
        if ( curr_bound_id != UNBOUND_ID) {
            getManager().getItem(curr_bound_id).bound_to_ = UNBOUND_ID;
        }
        getManager().texture_units_[slot_id] = getId();
        bound_to_ = slot_id;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot_id));
        GLCall(glBindTexture(GL_TEXTURE_2D, gl_handle_));
    }
}
