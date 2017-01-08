#include "ParticleBatchStates.h"
#include "../graphics_config.h"

namespace grynca {

    inline f32 ParticleBatchState::getMaxTime()const {
        return max_time_;
    }

    inline const Dir2& ParticleBatchState::getGravityDir()const {
        return gravity_dir_;
    }

    inline Dir2& ParticleBatchState::accGravityDir() {
        return gravity_dir_;
    }

    inline void ParticleBatchState::setGravityDir(const Dir2& gd) {
        gravity_dir_ = gd;
    }

    inline void ParticleBatchState::setMaxTime(f32 mt) {
        max_time_ = mt;
    }

    inline fast_vector<ParticleCPUData>& ParticleBatchState::accParticlesCpuData() {
        return cpu_data_;
    }

}