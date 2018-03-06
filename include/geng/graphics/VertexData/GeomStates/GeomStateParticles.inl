#include "GeomStateParticles.h"

namespace grynca {

    inline GeomStateParticles::GeomStateParticles(GeomStateType type_id, VertexData& vd, Index geom_id)
     : GeomStateBase(type_id, vd, geom_id),
       max_time_(0.0f), inv_max_time_(0.0f)
    {}

    inline f32 GeomStateParticles::getMaxTime()const {
        return max_time_;
    }

    inline f32 GeomStateParticles::getInvMaxTime()const {
        return inv_max_time_;
    }

    inline const Dir2& GeomStateParticles::getGravityDir()const {
        return gravity_dir_;
    }

    inline Dir2& GeomStateParticles::accGravityDir() {
        return gravity_dir_;
    }

    GeomStateParticles& GeomStateParticles::setGravityDir(const Dir2& gd) {
        gravity_dir_ = gd;
        return *this;
    }

    GeomStateParticles& GeomStateParticles::setMaxTime(f32 mt) {
        max_time_ = mt;
        inv_max_time_ = (max_time_!=0.0f)? 1.0f/max_time_ : 0.0f;
        return *this;
    }

    inline fast_vector<ParticleCPUData>& GeomStateParticles::accParticlesCpuData() {
        return cpu_data_;
    }

}