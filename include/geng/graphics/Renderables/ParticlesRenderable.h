#ifndef PARTICLESRENDERABLE_H
#define PARTICLESRENDERABLE_H

#include "Renderable.h"

namespace grynca {

    // fw
    class ParticleShader;
    class VertexDataParticles;

    // TODO: budu potrebovat aby geomy refcountovaly svuj GeomState
    //       to bude asi soucasti predelavky geomu na min obecnou classu

    class ParticlesRenderable : public Renderable
    {
    public:
        typedef ParticleShader ShaderType;
        typedef VertexDataParticles VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStream);

        ParticlesRenderable(const Renderer2D::ItemRef& rt);


        const Vec2& getParticlesSize()const;
        f32 getMaxTime()const;
        const Dir2& getGravityDir()const;
        u32 getTextureUnit()const;
        ARect getTextureRegion()const;

        Vec2& accParticlesSize();
        Dir2& accGravityDir();

        // [min, max]
        ParticlesRenderable& setParticlesSize(const Vec2& s);
        ParticlesRenderable& setMaxTime(f32 mt);
        ParticlesRenderable& setGravityDir(const Dir2& gd);
        ParticlesRenderable& setTextureUnit(u32 tid);
        ParticlesRenderable& setTextureRegion(const ARect &texture_coords);

        void addParticle(const Vec2& pos, Angle rot, Angle rot_speed, const Colorf& color,
                         const Vec2& speed, f32 weight, f32 time);
    private:
        Index batch_id_;
        VertexDataParticles* verts_;
    };


}

#include "ParticlesRenderable.inl"
#endif //PARTICLESRENDERABLE_H
