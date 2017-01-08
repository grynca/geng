#ifndef PARTICLEBATCHSTATES_H
#define PARTICLEBATCHSTATES_H

#include "types/Manager.h"
#include "maths/Vec2.h"

namespace grynca {

    // fw
    class ParticleBatchState;

    class ParticleBatchStates : public TightManager<ParticleBatchState>
    {
    public:
        typedef ManagedItemRef<ParticleBatchState> ItemRef;
    private:
    };

    // data for cpu computation only (are not sent to gpu)
    struct ParticleCPUData {
        Vec2 lin_speed;
        Angle rot_speed;
        Angle rotation;
        f32 weight;
        f32 time;
    };

    class ParticleBatchState : public ManagedItem<ParticleBatchStates>
    {
    public:
        f32 getMaxTime()const;
        const Dir2& getGravityDir()const;
        Dir2& accGravityDir();

        void setGravityDir(const Dir2& gd);
        void setMaxTime(f32 mt);

        fast_vector<ParticleCPUData>& accParticlesCpuData();
    private:
        f32 max_time_;
        Dir2 gravity_dir_;

        fast_vector<ParticleCPUData> cpu_data_;
    };

}

#include "ParticleBatchStates.inl"
#endif //PARTICLEBATCHSTATES_H
