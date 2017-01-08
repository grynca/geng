#include "VertexData.h"
#include "../Vertices.h"
#include "Geom.h"
#include <cassert>
#include "../graphics_config.h"

namespace grynca {

    inline VertexBuffer::VertexBuffer(u32 initial_alloc, GeomState::UsageHint uh)
     : size(0), holes_size(0), alloc_size(initial_alloc), last_geom(Index::Invalid()), usage_hint(uh)
    {
    }

    inline u32 VertexBuffer::getBackSpace()const {
        return alloc_size-size;
    }

    inline f32 VertexBuffer::calcBackFreeness()const {
        return (f32)getBackSpace()/alloc_size;
    }

    inline GLenum VertexBuffer::getGLUsageHint()const {
        switch (usage_hint) {
            default:
            case GeomState::uhStatic:
                return GL_STATIC_DRAW;
            case GeomState::uhDynamic:
                return GL_DYNAMIC_DRAW;
            case GeomState::uhStream:
                return GL_STREAM_DRAW;
        }
    }

    inline VertexData::VertexData()
     : vbo_initial_size_(config::INITIAL_VBO_SIZE), bound_buffer_id_(InvalidId()), vertex_size_(0)
    {
        memset(buffers_for_adding_, u8(-1), sizeof(u32)*GeomState::uhCount);
    }

    inline VertexData::~VertexData() {
        for (u32 i=0; i<buffers_.size(); ++i) {
            GLCall(glDeleteBuffers(1, &buffers_[i].vbo));
        }
    }

    inline void VertexData::bindVertexBuffer(u32 buffer_id) {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffers_[buffer_id].vbo));

        bound_buffer_id_ = buffer_id;
    }

    inline void VertexData::setVertexBufferInitialSize(u32 vbo_initial_size) {
        vbo_initial_size_ = vbo_initial_size;
    }

    inline void VertexData::bindBufferWithLayouts(u32 buffer_id) {

        // first buffer is vertex buffer
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffers_[buffer_id].vbo));
        for (u32 i=0; i<vbo_attribs_.size(); ++i) {
            GLCall(glEnableVertexAttribArray(vbo_attribs_[i].attrib_id));
            GLCall(glVertexAttribPointer(vbo_attribs_[i].attrib_id, vbo_attribs_[i].count, vbo_attribs_[i].type, (GLboolean)vbo_attribs_[i].normalized, vbo_attribs_[i].stride, reinterpret_cast<const GLvoid*>(vbo_attribs_[i].struct_offset)));
        }
        bound_buffer_id_ = buffer_id;
    }

    inline u32 VertexData::getBoundBufferId()const {
        return bound_buffer_id_;
    }

    template <typename Vertex>
    inline void VertexData::setVertexLayout(const fast_vector<VertexAttribInfo>& attribs) {
        vertex_size_ = u32(sizeof(Vertex));
        vbo_attribs_ = attribs;
    }

    inline u32 VertexData::getVertexSize() {
        return vertex_size_;
    }

    inline void VertexData::update(f32 dt) {

        f32 best_freeness[GeomState::uhCount] = {0.0f};

        // synces with gpu
        for (u32 buf_id = 0; buf_id<buffers_.size(); ++buf_id) {
            VertexBuffer& vb = buffers_[buf_id];

            float holes_ratio = f32(vb.holes_size)/vb.alloc_size;
            if (holes_ratio > VertexBuffer::compress_th) {
                compressBuffer_(buf_id);
            }
            else {
                updateGeoms_(buf_id);
            }

            f32 back_freeness = vb.calcBackFreeness();
            if (back_freeness > best_freeness[vb.usage_hint]) {
                best_freeness[vb.usage_hint] = back_freeness;
                buffers_for_adding_[vb.usage_hint] = buf_id;
            }
        }

        for (u32 i=0; i<GeomState::uhCount; ++i) {
            if (best_freeness[i] < 0.5f) {
                buffers_for_adding_[i] = InvalidId();
            }
        }
    }

    template <typename T>
    inline T VertexData::addWithFactory(GeomState::StateType state_type, GeomState::UsageHint buff_hint) {
        return T(*this, state_type, buff_hint);
    }

    inline std::string VertexData::getDebugString(u32 indent_cnt) {
        std::stringstream ss;
        std::string indent = string_utils::spaces(indent_cnt);

        ss << indent << "v_size=" << getVertexSize() << std::endl;
        for (u32 i=0; i<buffers_.size(); ++i) {
            VertexBuffer& vb = buffers_[i];
            std::string usage_str;
            switch (vb.usage_hint) {
                case GeomState::uhStatic:
                    usage_str = "static";
                    break;
                case GeomState::uhDynamic:
                    usage_str = "dynamic";
                    break;
                case GeomState::uhStream:
                    usage_str = "stream";
                    break;
                default:
                    usage_str = "invalid";
                    break;
            }

            f32 holes_ratio =f32(vb.holes_size)/vb.alloc_size;
            f32 back_freeness = vb.calcBackFreeness();
            u32 used = vb.size - vb.holes_size;
            f32 used_ratio = f32(used)/vb.alloc_size;
            ss << indent << "[" << i << "]: "
               << "GLid=" << vb.vbo << ", "
               << "cap=" << vb.alloc_size << "(" << vb.alloc_size*getVertexSize() << "b), "
               << "used=" << used << "(" << string_utils::printPerc(used_ratio) << "%), "
               << "holes=" << string_utils::printPerc(holes_ratio) << "%, "
               << "back_free=" << string_utils::printPerc(back_freeness) << "%, "
               << "usage=" << usage_str << std::endl;
        }
        return ss.str();
    }

    inline void VertexData::invalidateGeom_(Geom& g) {
        VertexBuffer& vb = buffers_[g.buffer_id_];
        vb.dirty_geoms.push_back(g.getId());
    }

    inline void VertexData::compressBuffer_(u32 buf_id) {
        VertexBuffer& vb = buffers_[buf_id];

#ifndef WEB     // webGL does not support gpu-side copy
        // bind prev vbo as read buffer
        GLuint prev_vbo = vb.vbo;
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, prev_vbo));
        // generate new vbo
        GLCall(glGenBuffers(1, &vb.vbo));
        bindVertexBuffer(buf_id);
        GLCall(glBufferData(GL_ARRAY_BUFFER, vb.alloc_size*vertex_size_, NULL, vb.getGLUsageHint()));
#else
        bindVertexBuffer(buf_id);
#endif
        // copy non-dirty geoms on gpu
        u32 buf_offset = 0;
        Index prev = Index::Invalid();
        Index curr = vb.last_geom;
        while (curr.isValid()) {
            // this actually reverses geoms linked list order, but that probably does not matter
            Geom& g = getItem(curr);
            if (g.isDirty()) {
                // skip dirty geoms
                curr = g.left_;
                continue;
            }

            u32 verts_cnt = g.getVerticesCount();
            u32 read_offset = g.start_offset_in_vbo_;
            g.start_offset_in_vbo_ = buf_offset;
            if (verts_cnt) {
                u32 size_bytes = verts_cnt*vertex_size_;
                u32 read_offset_bytes = read_offset*vertex_size_;
                u32 write_offset_bytes = buf_offset*vertex_size_;
#ifndef WEB
                GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, read_offset_bytes, write_offset_bytes, size_bytes));
#else
                GLCall(glBufferSubData(GL_ARRAY_BUFFER, g.start_offset_in_vbo_*vertex_size_, verts_cnt*vertex_size_, &g.vertices_data_[0]));
#endif
                buf_offset += verts_cnt;
            }

            Index next = g.left_;
            g.left_ = prev;
            g.right_ = next;

            prev = curr;
            curr = next;
        };

        vb.last_geom = prev;
        vb.holes_size = 0;
        vb.size = buf_offset;

        // push-back dirty geoms
        for (u32 i=0; i<vb.dirty_geoms.size(); ++i) {
            Geom &g = getItem(vb.dirty_geoms[i]);
            u32 new_size = g.getVerticesCount();
            pushBack_(vb, g, new_size);
            g.verts_cnt_vbo_ = new_size;
            if (new_size) {
                GLCall(glBufferSubData(GL_ARRAY_BUFFER, g.start_offset_in_vbo_*vertex_size_, new_size*vertex_size_, &g.vertices_data_[0]));
                buf_offset += new_size;
            }
            g.clearDirty_();
        }
        vb.dirty_geoms.clear();

#ifndef WEB
        // delete previous vbo
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, 0));
        GLCall(glDeleteBuffers(1, &prev_vbo));
#endif
    }

    inline void VertexData::updateGeoms_(u32 buf_id) {
        VertexBuffer& vb = buffers_[buf_id];

        if (!vb.dirty_geoms.empty()) {
            bindVertexBuffer(buf_id);

            for (u32 i=0; i<vb.dirty_geoms.size(); ++i) {

                Geom& g = getItem(vb.dirty_geoms[i]);
                u32 new_size = g.getVerticesCount();
                if (g.start_offset_in_vbo_ == InvalidId()) {
                    // new geom
                    pushBack_(vb, g, new_size);
                }
                else {
                    u32 prev_size = g.verts_cnt_vbo_;

                    if (new_size <= prev_size) {
                        g.verts_cnt_vbo_ = new_size;
                    }
                    else {
                        // already contained geom
                        u32 enlargement = new_size - prev_size;
                        // geom grew larger -> check if there is enough neighboring free space
                        if (g.right_.isValid() && g.getSpaceOnRight_() >= enlargement) {
                            // on right
                            vb.holes_size -= enlargement;
                        }
                        else if (g.left_.isValid() && g.getSpaceOnLeft_() >= enlargement) {
                            // on left
                            g.start_offset_in_vbo_ -= enlargement;
                            vb.holes_size -= enlargement;
                        }
                        else {
                            u32 prev_size = g.verts_cnt_vbo_;
                            vb.holes_size += prev_size;
                            g.unlink_();
                            pushBack_(vb, g, new_size);
                        }
                    }
                }
                g.verts_cnt_vbo_ = new_size;
                if (new_size > 0) {
                    // update data in vbo
                    GLCall(glBufferSubData(GL_ARRAY_BUFFER, g.start_offset_in_vbo_*vertex_size_, new_size*vertex_size_, &g.vertices_data_[0]));
                }
                g.clearDirty_();
            }
            vb.dirty_geoms.clear();
        }
    }

    inline void VertexData::addBuffer_(GeomState::UsageHint usage_hint) {
        u32 alloc_size_verts = std::ceil(f32(vbo_initial_size_)/vertex_size_);
        buffers_.emplace_back(alloc_size_verts, usage_hint);

        VertexBuffer& vb = buffers_.back();
        GLCall(glGenBuffers(1, &vb.vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb.vbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vbo_initial_size_, NULL, vb.getGLUsageHint()));
    }

    inline void VertexData::reallocVertexBuffer_(VertexBuffer& vb, u32 needed_size_verts) {
        // TODO: create version for webGL without gpu-side copy

        ASSERT(needed_size_verts > vb.alloc_size);

        needed_size_verts = std::max(vb.alloc_size*2, needed_size_verts);

        // realloc buffer on gpu
        GLuint buf;
        GLCall(glGenBuffers(1, &buf));
        u32 prev_alloc = vb.alloc_size;
        vb.alloc_size = needed_size_verts;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buf));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vb.alloc_size*vertex_size_, NULL, vb.getGLUsageHint()));
        if (prev_alloc != 0) {
            GLCall(glBindBuffer(GL_COPY_READ_BUFFER, vb.vbo));
            GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, prev_alloc));
            GLCall(glBindBuffer(GL_COPY_READ_BUFFER, 0));
        }
        GLCall(glDeleteBuffers(1, &vb.vbo));
        vb.vbo = buf;
    }

    inline void VertexData::pushBack_(VertexBuffer& vb, Geom& g, u32 new_size) {
        if ((vb.size+new_size) > vb.alloc_size) {
            // realloc vbo
            reallocVertexBuffer_(vb, vb.size+new_size);
        }

        // in the end
        g.start_offset_in_vbo_ = vb.size;

        vb.size += new_size;
        // fix linkage
        g.link_(vb.last_geom, Index::Invalid());
        vb.last_geom = g.getId();
    }

    template <typename VertexType>
    inline Items<VertexType> VertexData::accVertexData_(Geom& g) {
        return Items<VertexType>(g.vertices_data_);
    }

    inline void VertexData::setGeomVBOPos_(Geom& g, u32 start_offset, u32 count) {
        g.start_offset_in_vbo_ = start_offset;
        g.verts_cnt_vbo_ = count;
    }

    inline u32 VertexData::getBufferForNewGeom_(GeomState::UsageHint usage_hint) {
        u32 buf_id = buffers_for_adding_[usage_hint];
        if (buf_id == InvalidId()) {
            buf_id = u32(buffers_.size());
            addBuffer_(usage_hint);
            buffers_for_adding_[usage_hint] = buf_id;
        }
        return buf_id;
    }

    inline std::string VertexData::debugPrintLinkage_(u32 buf_id) {
        std::stringstream ss;

        fast_vector<Index> linkage;
        Index id = buffers_[buf_id].last_geom;
        while (id.isValid()) {
            if (std::find(linkage.begin(), linkage.end(), id) != linkage.end()) {
                ss << "!RECURSION! ";
                linkage.push_back(id);
                break;
            }
            linkage.push_back(id);
            id = getItem(id).left_;
        }

        for (i32 i=linkage.size()-1; i>=0; --i) {
            ss << linkage[i] << " <-";
        }
        return ss.str();
    }
}