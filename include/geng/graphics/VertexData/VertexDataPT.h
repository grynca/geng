#ifndef VERTEXDATAPT_H
#define VERTEXDATAPT_H

#include "maths/Vec2.h"
#include "VertexData.h"

namespace grynca {

    // fw
    class SpriteAnimationStates;
    class TextStates;

    class VertexDataPT : public VertexData {
    public:
        // used for sprites & texture fonts
        struct Vertex {
            Vec2 pos;
            Vec2 tc;
        };

        VertexDataPT();
        void init();

        ~VertexDataPT();

        TextStates& getTextStates();
        SpriteAnimationStates& getSpriteAnimationsStates();

        virtual void update(f32 dt) override;
    private:
        virtual Index beforeGeomChangedState_(Geom& g, GeomState::StateType old_type, GeomState::StateType new_type) override;
        virtual std::string getDebugName_() override { return "VertexDataPT"; }

        TextStates* text_states_;
        SpriteAnimationStates* anim_states_;
    };

}

#include "VertexDataPT.inl"
#endif //VERTEXDATAPT_H
