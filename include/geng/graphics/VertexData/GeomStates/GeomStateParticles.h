#ifndef GEOMSTATEPARTICLES_H
#define GEOMSTATEPARTICLES_H

#include "GeomStateBase.h"
#include "maths/Vec2.h"

namespace grynca {

    // data for cpu computation only (are not sent to gpu)
    struct ParticleCPUData {
        Vec2 lin_speed;
        Angle ang_speed;
        f32 weight;
        f32 time;
    };

    class GeomStateParticles : public GeomStateBase {
    public:
        GeomStateParticles(GeomStateType type_id, VertexData& vd, Index geom_id);

        f32 getMaxTime()const;
        f32 getInvMaxTime()const;
        const Dir2& getGravityDir()const;
        Dir2& accGravityDir();

        GeomStateParticles& setGravityDir(const Dir2& gd);
        GeomStateParticles& setMaxTime(f32 mt);

        fast_vector<ParticleCPUData>& accParticlesCpuData();
    private:
        f32 max_time_;
        f32 inv_max_time_;
        Dir2 gravity_dir_;

        fast_vector<ParticleCPUData> cpu_data_;
    };

}

#include "GeomStateParticles.inl"
#endif //GEOMSTATEPARTICLES_H
