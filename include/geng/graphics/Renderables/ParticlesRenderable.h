#ifndef PARTICLESRENDERABLE_H
#define PARTICLESRENDERABLE_H

#include "Renderable.h"

namespace grynca {

    // fw
    class ParticleShader;
    class VertexDataParticles;
    class GeomStateParticles;

    // TODO: budu potrebovat aby geomy refcountovaly svuj GeomState
    //       to bude asi soucasti predelavky geomu na min obecnou classu

    class ParticlesRenderable : public Renderable
    {
    public:
        typedef ParticleShader ShaderType;
        typedef VertexDataParticles VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStream;

        struct DrawData : public Renderable::DrawData {
            Vec2 size;    // min, max
            f32 vp_zoom;    // viewport zoom
            u32 texture;
            Mat3 tr_transform;   // for transforming to correct texture region
        };

        ParticlesRenderable();

        void setNewGeom();

        const GeomStateParticles& getParticlesState()const;

        const Vec2& getParticlesSize()const;
        u32 getTextureUnit()const;
        ARect getTextureRegion()const;

        GeomStateParticles& accParticlesState();
        Vec2& accParticlesSize();

        // [min, max]
        void setParticlesSize(const Vec2& s);
        void setImage(const ImagePos& img_pos);
        void setTextureUnit(u32 tid);
        void setTextureRegion(const ARect &texture_coords);

        void addParticle(const Vec2& pos, const Dir2& rot_dir, const Vec2& lin_vel, Angle ang_vel, const Colorf& color, f32 weight, f32 time);

        void onBeforeDraw(Shader& s);
    private:
        friend class Renderable;

        VertexDataParticles* verts_;
    };


}

#include "ParticlesRenderable.inl"
#endif //PARTICLESRENDERABLE_H
