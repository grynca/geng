#include "VertexDataParticles.h"

namespace grynca {

    inline VertexDataParticles::VertexDataParticles()
     : next_take_from_(0)
    {
#ifndef WEB
        GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
        // there will be one geom for each batch of particles

        setVertexLayout<Vertex>({
            { Shader::getVertexAttribId("v_pos_rot"), 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos) },
            { Shader::getVertexAttribId("v_color_l"), 4, GL_FLOAT, true, sizeof(Vertex), offsetof(Vertex, colorl) }
        });

        //only one vertex buf
        setVertexBufferInitialSize(sizeof(Vertex)*config::PARTICLES_MAX);
        buffers_for_adding_[GeomState::uhStream] = 0;
        addBuffer_(GeomState::uhStream);
    }

    inline ParticleBatchStates& VertexDataParticles::getParticleBatchStates() {
        return batches_;
    }

    inline void VertexDataParticles::addParticle(Index geom_id, ParticleGPUData*& gpu_data_out, ParticleCPUData*& cpu_data_out) {

        u32& particles_cnt = buffers_[0].size;
        if (particles_cnt >= config::PARTICLES_MAX) {
            // remove particle from some other batch via round-robin fashion
            u32 geoms_cnt = getItemsCount();
            for (u32 i=0; i<geoms_cnt; ++i) {
                Geom& g = getItemAtPos2(next_take_from_);
                Items<Vertex> gpu_data = accVertexData_<Vertex>(g);
                u32 batch_size = gpu_data.size();
                if (batch_size) {
                    ParticleBatchState &batch = batches_.getItem(g.getGeomStateId());
                    fast_vector<ParticleCPUData> &cpu_data = batch.accParticlesCpuData();

                    // remove first particle
                    cpu_data.front() = cpu_data.back();
                    cpu_data.pop_back();
                    gpu_data.front() = gpu_data.back();
                    gpu_data.pop_back();
                    --particles_cnt;
                    break;
                }
                next_take_from_ = (next_take_from_+1) % geoms_cnt;
            }
        }

        // add new particle
        Geom& g = getItem(geom_id);
        ParticleBatchState& batch = batches_.getItem(g.getGeomStateId());
        Items<Vertex> gpu_data = accVertexData_<Vertex>(g);

        u32 new_pid = u32(batch.accParticlesCpuData().size());
        batch.accParticlesCpuData().emplace_back();
        gpu_data.emplace_back();

        gpu_data_out = &gpu_data[new_pid];
        cpu_data_out = &batch.accParticlesCpuData()[new_pid];
        ++particles_cnt;
    }

    inline u32 VertexDataParticles::getParticlesCount()const {
        return buffers_[0].size;
    }

    inline void VertexDataParticles::update(f32 dt) {
        if (buffers_.empty())
            return;
        bindVertexBuffer(0);
        u32& particles_cnt = buffers_[0].size;
        u32 buf_offset = 0;
        for (u32 i=0; i<getItemsCount(); ++i) {
            Geom& g = getItemAtPos2(i);
            ParticleBatchState& batch = batches_.getItem(g.getGeomStateId());
            fast_vector<ParticleCPUData>& cpu_data = batch.accParticlesCpuData();
            Items<Vertex> gpu_data = accVertexData_<Vertex>(g);
            u32 batch_size = gpu_data.size();

            for (u32 j = 0; j<batch_size; ) {
                ParticleCPUData& cpud = cpu_data[j];
                ParticleGPUData& gpud = gpu_data[j];
                cpud.time += dt;
                if (cpud.time > batch.getMaxTime()) {
                    // particle died -> move here some alive from end
                    cpud = cpu_data.back();
                    cpu_data.pop_back();

                    gpud = gpu_data.back();
                    gpu_data.pop_back();
                    --batch_size;
                    --particles_cnt;
                }
                else {
                    gpud.colorl.a = cpud.time/batch.getMaxTime();

                    // simulate particle
                    cpud.lin_speed += batch.getGravityDir()*cpud.weight*dt;
                    cpud.rotation += cpud.rot_speed*dt;
                    cpud.rotation.getSinCos(gpud.sin_r, gpud.cos_r);
                    gpud.pos += cpud.lin_speed*dt;
                    ++j;
                }
            }

            setGeomVBOPos_(g, buf_offset, batch_size);
            if (batch_size == 0)
                continue;

            GLCall(glBufferSubData(GL_ARRAY_BUFFER, buf_offset*sizeof(ParticleGPUData), batch_size*sizeof(ParticleGPUData), gpu_data.getDataPtr()));
            buf_offset += batch_size;
        }
    }

    inline Index VertexDataParticles::beforeGeomChangedState_(Geom& g, GeomState::StateType old_type, GeomState::StateType new_type) {
        Index new_state_id = Index::Invalid();
        switch (old_type) {
            case GeomState::stParticles:
                batches_.removeItem(g.getGeomStateId());
                break;
            case GeomState::stNone:
            default:
                break;
        }

        switch (new_type) {
            case GeomState::stParticles: {
                ParticleBatchState& s = batches_.addItem();
                new_state_id = s.getId();
            }break;
            case GeomState::stNone:
            default:
                break;
        }
        return new_state_id;
    }

}