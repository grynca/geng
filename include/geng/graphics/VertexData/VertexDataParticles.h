#ifndef VERTEXDATAPARTICLES_H
#define VERTEXDATAPARTICLES_H

#include "maths/Vec2.h"
#include "VertexData.h"
#include "../Renderer2D.h"
#include "../Renderables/Renderable.h"
#include "../Shaders/ParticleShader.h"
#include "assets/Image.h"
#include "ParticleBatchStates.h"

namespace grynca {

    class VertexDataParticles : public VertexData {
    public:

        struct Vertex {
            Vec2 pos;
            float sin_r, cos_r;

            Colorf colorl;   // life 0-1 encoded in alpha value
        };

        VertexDataParticles();

        ParticleBatchStates& getParticleBatchStates();

        void addParticle(Index geom_id, Vertex*& gpu_data_out, ParticleCPUData*& cpu_data_out);
        u32 getParticlesCount()const;

        virtual void update(f32 dt) override;
    private:
        friend class ParticleBatchState;

        virtual Index beforeGeomChangedState_(Geom& g, GeomState::StateType old_type, GeomState::StateType new_type) override;
        virtual std::string getDebugName_() override { return "VertexDataParticles"; }

        u32 next_take_from_;

        ParticleBatchStates batches_;
    };

    typedef VertexDataParticles::Vertex ParticleGPUData;
}

#include "VertexDataParticles.inl"
#endif //VERTEXDATAPARTICLES_H
