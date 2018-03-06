#ifndef GEOM_H
#define GEOM_H

#include "types/Manager.h"
#include "functions/common.h"
#include "../glinclude.h"
#include "geom_enums.h"
#include <bitset>

namespace grynca {
    // fw
    class VertexData;
    class GeomState;
    class GeomStateBase;

    class Geom : public ManagedItem<VertexData> {
    public:
        Geom(GLenum primitive_type, GeomUsageHint buff_hint);
        ~Geom();
        void afterAdded();

        u32 getVerticesCount()const;
        u32 getVerticesBytesSize()const;

        GeomUsageHint getUsageHint()const;
        bool isDirty()const;
        u16 getVertexBufferId()const;

        template <typename Vertex>
        void addVertices(const fast_vector<Vertex>& vs);
        template <typename Vertex>
        void addVertex(const Vertex& v);
        template <typename Vertex>
        const Vertex& getVertex(u32 id)const;
        template <typename Vertex>
        Vertex& accVertex(u32 id);     // also sets dirty flag (will be updated to gpu on next sync)
        void removeVertex(u32 id);
        void removeAllVertices();

        template <typename Vertex>
        void collectVertices(fast_vector<Vertex>& vertices_out);

        u32 getVertsCountVbo()const;
        void render();

        GLenum getPrimitiveType();

        template <typename T>
        T getFactory();

        // Geom State
        GeomStateType getStateType()const;
        u32 getStateId()const;
        const GeomStateBase& getState()const;
        GeomStateBase& accState();
        GeomStateBase* setState(GeomStateType st);      // returns NULL when setting None state

        // for debug
        fast_vector<f32> loadDataFromGPU();
    protected:
        friend class VertexData;
        friend class GeomStates;

        void setUsageHint_(GeomUsageHint buff_hint);
        void setStateId_(u32 state_id);
        void link_(Index left, Index right);
        void unlink_();
        u32 getSpaceOnRight_();
        u32 getSpaceOnLeft_();

        void makeDirty_();
        void clearDirty_();       // correct vbo must be bound

        u16 buffer_id_;
        u32 bits_pack_;
        GLenum primitive_type_;
        u32 start_offset_in_vbo_;
        u32 verts_cnt_vbo_;
        u32 state_id_;
        // neighbor geoms
        Index left_, right_;
        fast_vector<u8> vertices_data_;


        static constexpr u32 BIT_DIRTY = 0;
        static constexpr u32 BIT_USAGE_HINT_START = 1;
        static constexpr u32 BIT_USAGE_HINT_CNT = floorLog2(uhCount-1);
        static constexpr u32 BIT_STATE_TYPE_START = BIT_USAGE_HINT_START +  BIT_USAGE_HINT_CNT;
        static constexpr u32 BIT_STATE_TYPE_CNT = floorLog2(gstCount-1);
    };
}

#include "Geom.inl"
#endif //GEOM_H
