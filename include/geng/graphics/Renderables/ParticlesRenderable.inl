#include "ParticlesRenderable.h"
#include "../Shaders/ParticleShader.h"
#include "../VertexData/VertexDataParticles.h"

namespace grynca {

    inline ParticlesRenderable::ParticlesRenderable() {
        verts_ = &accWindow().getVertices().getFast<VertexDataParticles>();
    }

    inline void ParticlesRenderable::setNewGeom() {
        // particle vertices are always streamed
        Geom& new_geom = verts_->addItem(GL_POINTS, GeomUsageHint::uhStream);
        new_geom.setState(gstParticles);
        setGeom(new_geom);
    }

    inline const GeomStateParticles& ParticlesRenderable::getParticlesState()const {
        const Geom& geom = getRenderTaskPtr()->getGeom().get();
        ASSERT(geom.getStateType() == GeomStateType::gstParticles);
        return (const GeomStateParticles&)(geom.getState());
    }

    inline const Vec2& ParticlesRenderable::getParticlesSize()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().size;
    }

    inline u32 ParticlesRenderable::getTextureUnit()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().texture;
    }

    inline ARect ParticlesRenderable::getTextureRegion()const {
        const DrawData& dd = getRenderTaskPtr()->getDrawDataAs<DrawData>();
        // extract from transform matrix
        f32 w = dd.tr_transform.val(0, 0);
        f32 h = dd.tr_transform.val(1, 1);
        f32 x = dd.tr_transform.val(2, 0) - w*0.5f;
        f32 y = dd.tr_transform.val(2, 1) - h*0.5f;
        return ARect({x, y}, {w, h});
    }

    inline GeomStateParticles& ParticlesRenderable::accParticlesState() {
        Geom& geom = accRenderTaskPtr()->accGeom().acc();
        ASSERT(geom.getStateType() == GeomStateType::gstParticles);
        return (GeomStateParticles&)(geom.accState());
    }

    inline Vec2& ParticlesRenderable::accParticlesSize() {
        return accRenderTaskPtr()->accDrawDataAs<DrawData>().size;
    }

    inline void ParticlesRenderable::setParticlesSize(const Vec2& s) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().size = s;
    }

    inline void ParticlesRenderable::setImage(const ImagePos& img_pos) {
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.texture = img_pos.getTextureId();
        const ARect& texture_coords = img_pos.getTextureRegion()->getTextureRect();
        Vec2 size = texture_coords.getSize();
        dd.tr_transform.val(0, 0) = size.getX();
        dd.tr_transform.val(1, 1) = size.getY();
        dd.tr_transform.val(2, 0) = texture_coords.getX() + size.getX()*0.5f;
        dd.tr_transform.val(2, 1) = texture_coords.getY() + size.getY()*0.5f;
    }

    inline void ParticlesRenderable::setTextureUnit(u32 tid) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().texture = tid;
    }

    inline void ParticlesRenderable::setTextureRegion(const ARect &texture_coords) {
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        Vec2 size = texture_coords.getSize();
        dd.tr_transform.val(0, 0) = size.getX();
        dd.tr_transform.val(1, 1) = size.getY();
        dd.tr_transform.val(2, 0) = texture_coords.getX() + size.getX()*0.5f;
        dd.tr_transform.val(2, 1) = texture_coords.getY() + size.getY()*0.5f;
    }

    inline void ParticlesRenderable::addParticle(const Vec2& pos, const Dir2& rot_dir, const Vec2& lin_vel, Angle ang_vel, const Colorf& color, f32 weight, f32 time) {
        ParticleGPUData* gpu_data;
        ParticleCPUData* cpu_data;
        verts_->addParticle(getRenderTaskPtr()->getGeom().getItemId(), gpu_data, cpu_data);
        gpu_data->pos = pos;
        gpu_data->colorl = color;
        gpu_data->rot_dir = rot_dir;

        cpu_data->lin_speed = lin_vel;
        cpu_data->ang_speed = ang_vel;
        cpu_data->weight = weight;
        cpu_data->time = time;
    }

    inline void ParticlesRenderable::onBeforeDraw(Shader& s) {
        ParticleShader& ps = (ParticleShader&)s;
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.vp_zoom = accWindow().getViewPort().getZoom().getX();
        ps.setUniforms(dd);
    }
}