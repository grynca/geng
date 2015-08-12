#ifndef VERTEXDATAPT_H
#define VERTEXDATAPT_H

#include "maths/Vec2.h"
#include "../VertexData.h"

namespace grynca {

    class VertexDataPT : public VertexData {
    public:
        // used for sprites & texture fonts
        struct Vertex {
            Vec2 pos;
            Vec2 tc;
        };

        VertexDataPT() {
            setVertexAttribs<Vertex>({ {4, GL_FLOAT, false, 0} });
        }
    };

}

#endif //VERTEXDATAPT_H
