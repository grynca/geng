#ifndef VERTEXDATAPT_H
#define VERTEXDATAPT_H

#include "maths/Vec2.h"
#include "VertexData.h"

namespace grynca {

    class VertexDataPT : public VertexData {
    public:
        // used for sprites & texture fonts
        struct Vertex {
            Vec2 pos;
            Vec2 tc;
        };

        VertexDataPT() : VertexData("VertexDataPT") {}

        void initSingleton();

        virtual void update(f32 dt) override;
    };

}

#include "VertexDataPT.inl"
#endif //VERTEXDATAPT_H
