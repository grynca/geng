#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "../glinclude.h"
#include "../Shaders/Shader.h"
#include "../NormOffset.h"
#include "types/Manager.h"
#include "types/containers/Items.h"
#include "geom_enums.h"
#include <stdint.h>

namespace grynca {

    // fw
    class Geom;
    class GeomStates;
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

        VertexBuffer(u32 initial_alloc, GeomUsageHint uh);

        u32 getBackSpace()const;
        f32 calcBackFreeness()const;
        GLenum getGLUsageHint()const;

        GLuint vbo;
        u32 size;       // data end
        u32 holes_size;
        u32 alloc_size;
        Index last_geom;
        GeomUsageHint usage_hint;

        // geoms in need of syncing to gpu
        fast_vector<Index> dirty_geoms;
    };

    class VertexData : public ManagedItemSingleton<Vertices>,
                       public TightManager<Geom> {
        friend class Geom;
    public:
        VertexData(const std::string& name);
        virtual ~VertexData();

        void setVertexBufferInitialSize(u32 vbo_initial_size);
        void bindVertexBuffer(u16 buffer_id);   // binds vbo
        void bindBufferWithLayouts(u16 buffer_id);   // binds vbo
        u32 getBoundBufferId()const;

        template <typename Vertex>
        void setVertexLayout(const fast_vector<VertexAttribInfo>& attribs);

        u32 getVertexSize()const;

        virtual void update(f32 dt);

        template <typename T>
        T addWithFactory(GeomUsageHint buff_hint);

        const GeomStates& getGeomStates()const;
        GeomStates& accGeomStates();

        // TODO: this is used only by VertexDataP, maybe move it there ?
        template <typename VertexType>
        void initSharedQuadGeomPositions();
        Geom& accSharedUnitQuadGeom(NormOffset::Type offset_type);

        const std::string& getName()const;
        std::string getDebugString(u32 indent_cnt)const;
    protected:
        friend class Vertices;

        void invalidateGeom_(Geom& g);
        void compressBuffer_(u16 buf_id);
        void updateGeoms_(u16 buf_id);
        void addBuffer_(GeomUsageHint usage_hint);
        void reallocVertexBuffer_(VertexBuffer& vb, u32 needed_size_verts);
        void pushBack_(VertexBuffer& vb, Geom& g, u32 new_size);
        template <typename VertexType>
        ItemsRef<VertexType> accVertexData_(Geom& g);       // internal, does not do dirtying
        void setGeomVBOPos_(Geom& g, u32 start_offset, u32 count);
        u16 getBufferForNewGeom_(GeomUsageHint usage_hint);
        std::string debugPrintLinkage_(u16 buf_id);

        std::string name_;
        u32 vbo_initial_size_;
        u16 bound_buffer_id_;
        u32 vertex_size_;
        u16 buffers_for_adding_[uhCount];
        fast_vector<VertexBuffer> buffers_;
        fast_vector<VertexAttribInfo> vbo_attribs_;
        GeomStates* geom_states_;

        Index shared_quad_geoms_[NormOffset::otCount];
    };

}

#include "VertexData.inl"
#endif //VERTEXDATA_H
