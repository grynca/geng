#ifndef VERTEXDATAPARTICLES_H
#define VERTEXDATAPARTICLES_H

#include "maths/Vec2.h"
#include "VertexData.h"
#include "assets.h"

namespace grynca {

    // fw
    class GeomStateParticles;
    class ParticleCPUData;

    class VertexDataParticles : public VertexData {
    public:

        struct Vertex {
            Vec2 pos;
            Dir2 rot_dir;

            Colorf colorl;   // life 0-1 encoded in alpha value
        };

        VertexDataParticles();
        void initSingleton();

        void addParticle(Index geom_id, Vertex*& gpu_data_out, ParticleCPUData*& cpu_data_out);
        u32 getParticlesCount()const;

        virtual void update(f32 dt) override;
    private:
        GeomStateParticles& getBatchState_(Geom& g);

        u32 next_take_from_;
    };

    typedef VertexDataParticles::Vertex ParticleGPUData;
}

#include "VertexDataParticles.inl"
#endif //VERTEXDATAPARTICLES_H
