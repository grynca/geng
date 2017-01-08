#include "ParticlesRenderable.h"
#include "../Shaders/ParticleShader.h"
#include "../VertexData/VertexDataParticles.h"

namespace grynca {

    inline VertexData::ItemRef ParticlesRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        ASSERT_M(usage_hint == GeomState::uhStream, "Particles vertices are always streamed.");

        VertexDataParticles& verts = w.getVertices().get<VertexDataParticles>();
        return verts.addItem(GL_POINTS, GeomState::stParticles, usage_hint);
    }

    inline ParticlesRenderable::ParticlesRenderable(const Renderer2D::ItemRef& rt)
     : Renderable(rt), batch_id_(getRenderTask()->getGeom()->getGeomStateId()),
       verts_(&getWindow().getVertices().get<VertexDataParticles>())
    {}


    inline const Vec2& ParticlesRenderable::getParticlesSize()const {
        return getRenderTask()->getUniformsAs<ParticleShader::Uniforms>().size;
    }

    inline f32 ParticlesRenderable::getMaxTime()const {
        ParticleBatchState& batch_state = verts_->getParticleBatchStates().getItem(batch_id_);
        return batch_state.getMaxTime();
    }

    inline const Dir2& ParticlesRenderable::getGravityDir()const {
        ParticleBatchState& batch_state = verts_->getParticleBatchStates().getItem(batch_id_);
        return batch_state.getGravityDir();
    }

    inline u32 ParticlesRenderable::getTextureUnit()const {
        return getRenderTask()->getUniformsAs<ParticleShader::Uniforms>().texture;
    }

    inline ARect ParticlesRenderable::getTextureRegion()const {
        const ParticleShader::Uniforms& us = getRenderTask()->getUniformsAs<ParticleShader::Uniforms>();
        // extract from transform matrix
        f32 w = us.tr_transform.val(0, 0);
        f32 h = us.tr_transform.val(1, 1);
        f32 x = us.tr_transform.val(2, 0) - w*0.5f;
        f32 y = us.tr_transform.val(2, 1) - h*0.5f;
        return ARect({x, y}, {w, h});
    }

    inline Vec2& ParticlesRenderable::accParticlesSize() {
        return accRenderTask()->getUniformsAs<ParticleShader::Uniforms>().size;
    }

    inline Dir2& ParticlesRenderable::accGravityDir() {
        ParticleBatchState& batch_state = verts_->getParticleBatchStates().getItem(batch_id_);
        return batch_state.accGravityDir();
    }

    inline ParticlesRenderable& ParticlesRenderable::setParticlesSize(const Vec2& s) {
        accRenderTask()->getUniformsAs<ParticleShader::Uniforms>().size = s;
        return *this;
    }

    inline ParticlesRenderable& ParticlesRenderable::setMaxTime(f32 mt) {
        ParticleBatchState& batch_state = verts_->getParticleBatchStates().getItem(batch_id_);
        batch_state.setMaxTime(mt);
        return *this;
    }

    inline ParticlesRenderable& ParticlesRenderable::setGravityDir(const Dir2& gd) {
        ParticleBatchState& batch_state = verts_->getParticleBatchStates().getItem(batch_id_);
        batch_state.setGravityDir(gd);
        return *this;
    }

    inline ParticlesRenderable& ParticlesRenderable::setTextureUnit(u32 tid) {
        accRenderTask()->getUniformsAs<ParticleShader::Uniforms>().texture = tid;
        return *this;
    }

    inline ParticlesRenderable& ParticlesRenderable::setTextureRegion(const ARect &texture_coords) {
        ParticleShader::Uniforms& us = accRenderTask()->getUniformsAs<ParticleShader::Uniforms>();
        Vec2 size = texture_coords.getSize();
        us.tr_transform.val(0, 0) = size.getX();
        us.tr_transform.val(1, 1) = size.getY();
        us.tr_transform.val(2, 0) = texture_coords.getX() + size.getX()*0.5f;
        us.tr_transform.val(2, 1) = texture_coords.getY() + size.getY()*0.5f;
        return *this;
    }

    inline void ParticlesRenderable::addParticle(const Vec2& pos, Angle rot, Angle rot_speed, const Colorf& color, const Vec2& speed, f32 weight, f32 time) {
        ParticleGPUData* gpu_data;
        ParticleCPUData* cpu_data;
        verts_->addParticle(getRenderTask()->getGeom().getItemId(), gpu_data, cpu_data);
        gpu_data->pos = pos;
        gpu_data->colorl = color;

        cpu_data->rotation = rot;
        cpu_data->lin_speed = speed;
        cpu_data->rot_speed = rot_speed;
        cpu_data->weight = weight;
        cpu_data->time = time;
    }
}