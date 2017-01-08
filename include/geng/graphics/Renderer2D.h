#ifndef RENDERER_H
#define RENDERER_H

#include "CoordFrame.h"
#include "graphics_config.h"
#include "Renderables/RenderIndex.h"
#include "types/containers/Array.h"
#include "maths/Transform.h"
#include <map>

namespace grynca {

    // fw
    class Window;
    class Geom;
    class Renderer2D;

    struct RenderTask : public ManagedItem<Renderer2D> {
        RenderTask();

        void setTransform(const Mat3& tm);
        void setLayer(u16 layer_id);
        void setCoordFrame(CoordFrame cf);
        void setGeom(const VertexData::ItemRef& g);

        const VertexData::ItemRef& getGeom()const;
        Index getGeomId()const;
        CoordFrame getCoordFrame()const;
        const RenderIndex& getRenderIndex()const;
        const Transform& getLocalTransform()const;

        Transform& accLocalTransform();
        RenderIndex& accRenderIndex();
        VertexData::ItemRef& accGeom();

        template <typename T>
        T& getUniformsAs();
        template <typename T>
        const T& getUniformsAs()const;
        u8* getUniformsData() { return uniforms_; }

        void calcTransform(Window& window, const Mat3& obj_tr_m);
        void setTransformMatrix(const Mat3& mat);
    private:
        static f32 calcLayerZ_(u32 layer_id);

        RenderIndex rid_;
        Transform local_transform_;
        VertexData::ItemRef geom_ref_;
        CoordFrame coord_frame_;
        u8 uniforms_[config::SHADER_UNIFORMS_SIZE];
    };

    class Renderer2D : public TightManager<RenderTask> {
    public:
        Renderer2D(Window& w);

        void scheduleForNextFrame(Index rt_id);

        void render();
        Window& getWindow();
    private:
        friend class RenderTask;

        Window* window_;

        std::map< u32 /*rend_id*/, fast_vector<u32> /* task positions */ > to_render_;
    };

}


#include "Renderer2D.inl"
#endif //RENDERER_H
