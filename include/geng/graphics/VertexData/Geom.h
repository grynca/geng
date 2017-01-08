#ifndef GEOM_H
#define GEOM_H

#include "types/Manager.h"
#include "../glinclude.h"
#include "GeomState.h"
#include <bitset>

namespace grynca {
    // fw
    class VertexData;

    class Geom : public ManagedItem<VertexData> {
    public:
        Geom(GLenum primitive_type, GeomState::StateType state_type, GeomState::UsageHint buff_hint);
        ~Geom();
        void init();

        u32 getVerticesCount()const;
        u32 getVerticesBytesSize()const;

        bool isDirty()const;
        u32 getVertexBufferId()const;

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

        void render();

        GLenum getPrimitiveType();

        template <typename T>
        T getFactory();

        // Geom State
        GeomState::StateType getGeomStateType()const;
        void setGeomStateType(GeomState::StateType st);    // this will destroy previous geom state
        Index getGeomStateId()const;

        // for debug
        fast_vector<float> loadDataFromGPU();
    protected:
        friend class VertexData;

        void link_(Index left, Index right);
        void unlink_();
        u32 getSpaceOnRight_();
        u32 getSpaceOnLeft_();

        void makeDirty_();
        void clearDirty_();       // correct vbo must be bound

        u8 pack_;
        GLenum primitive_type_;
        u32 buffer_id_;
        u32 start_offset_in_vbo_;
        u32 verts_cnt_vbo_;
        // neighbor geoms
        Index left_, right_;
        GeomState state_;

        fast_vector<u8> vertices_data_;
    };
}

#include "Geom.inl"
#endif //GEOM_H
