#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "../glinclude.h"
#include "../Shader.h"
#include "types/Manager.h"
#include "types/containers/Items.h"
#include "GeomState.h"
#include <stdint.h>

namespace grynca {

    // fw
    class Geom;
    class Vertices;

    struct VertexAttribInfo {
        VertexAttribInfo() : attrib_id(InvalidId()) {}
        VertexAttribInfo(u32 attrib_id, u32 count, GLenum type, bool normalized, u32 stride, u32 struct_offset)
         : attrib_id(attrib_id), count(count), type(type), normalized(normalized),
           stride(stride), struct_offset(struct_offset)
        {}

        bool isValid() { return attrib_id != InvalidId(); }

        u32 attrib_id;
        u32 count;
        GLenum type;
        bool normalized;
        u32 stride;
        u32 struct_offset;
    };

    struct VertexBuffer {
        static constexpr float compress_th = 0.4f;

        VertexBuffer(u32 initial_alloc, GeomState::UsageHint uh);

        u32 getBackSpace()const;
        f32 calcBackFreeness()const;
        GLenum getGLUsageHint()const;

        GLuint vbo;
        u32 size;       // data end
        u32 holes_size;
        u32 alloc_size;
        Index last_geom;
        GeomState::UsageHint usage_hint;

        // geoms in need of syncing to gpu
        fast_vector<Index> dirty_geoms;
    };

    class VertexData : public ManagedItemSingleton<Vertices>,
                       public TightManager<Geom> {
        friend class Geom;
    public:
        VertexData();
        void init() {}
        virtual ~VertexData();

        void setVertexBufferInitialSize(u32 vbo_initial_size);
        void bindVertexBuffer(u32 buffer_id);   // binds vbo
        void bindBufferWithLayouts(u32 buffer_id);   // binds vbo
        u32 getBoundBufferId()const;

        template <typename Vertex>
        void setVertexLayout(const fast_vector<VertexAttribInfo>& attribs);

        u32 getVertexSize();

        virtual void update(f32 dt);

        template <typename T>
        T addWithFactory(GeomState::StateType state_type, GeomState::UsageHint buff_hint);

        std::string getDebugString(u32 indent_cnt);
    protected:
        friend class Vertices;

        struct AuxBuffer {
            u32 size;
            fast_vector<VertexAttribInfo> attribs;
        };

        void invalidateGeom_(Geom& g);
        void compressBuffer_(u32 buf_id);
        void updateGeoms_(u32 buf_id);
        void addBuffer_(GeomState::UsageHint usage_hint);
        void reallocVertexBuffer_(VertexBuffer& vb, u32 needed_size_verts);
        void pushBack_(VertexBuffer& vb, Geom& g, u32 new_size);
        template <typename VertexType>
        Items<VertexType> accVertexData_(Geom& g);       // internal, does not do dirtying
        void setGeomVBOPos_(Geom& g, u32 start_offset, u32 count);
        u32 getBufferForNewGeom_(GeomState::UsageHint usage_hint);
        std::string debugPrintLinkage_(u32 buf_id);

        virtual Index beforeGeomChangedState_(Geom& g, GeomState::StateType old_type, GeomState::StateType new_type) { return Index::Invalid(); }        // returns new state id
        virtual std::string getDebugName_() = 0;

        u32 vbo_initial_size_;
        u32 bound_buffer_id_;
        u32 vertex_size_;
        u32 buffers_for_adding_[GeomState::uhCount];
        fast_vector<VertexBuffer> buffers_;
        fast_vector<VertexAttribInfo> vbo_attribs_;
    };

}

#include "VertexData.inl"
#endif //VERTEXDATA_H
