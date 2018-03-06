#ifndef RENDERER_H
#define RENDERER_H

#include "graphics_config.h"
#include "Renderables/RenderBatchId.h"
#include "types/containers/Array.h"
#include "maths/Transform.h"
#include <map>

namespace grynca {

    // fw
    class Window;
    class Geom;
    class Renderer2D;
    class GeomStateBase;
    class Shader;

    struct RenderTask : public ManagedItem<Renderer2D> {
        void setRenderableTypeId(u8 rtid);
        void setZFromLayerId(u16 layer_id);
        void setGeom(const VertexData::IRefPtr& g);
        void setTransformMat(const Mat3& tm);       // the final tr. matrix for rendering

        const VertexData::IRefPtr& getGeom()const;
        Index getGeomId()const;
        const GeomStateBase& getGeomState()const;
        const Mat3& getTransformMat()const;
        u8* getDrawData();
        u8 getRenderableTypeId()const;
        template <typename T>
        T& accDrawDataAs();
        template <typename T>
        const T& getDrawDataAs()const;
        u16 getLayerIdFromZ()const;

        GeomStateBase& accGeomState();
        VertexData::IRefPtr& accGeom();
        Mat3& accTransformMat();

        RenderBatchId calcRenderBatchId()const;

        void cloneTo(RenderTask& rt_out)const;
    private:
        static f32 layerIdToZ_(u16 layer_id);
        static u16 ZToLayerId_(f32 z_coord);

        u8 draw_data_[config::DRAW_DATA_SIZE];
        u8 renderable_type_id_;
        // ref counted, geoms can be shared for multiple render tasks
        VertexData::IRefPtr geom_ref_;
    };

    class Renderer2D : public Manager<RenderTask> {
    public:
        Renderer2D(Window& w);

        template <typename Types>
        void initRenderableTypes();

        void scheduleForNextFrame(Index rt_id, const Mat3& transform_mat, RenderBatchId batch_id);  // faster with cached RenderBatchId
        void scheduleForNextFrame(Index rt_id, const Mat3& transform_mat);

        void render();
        Window& getWindow();

        template <typename RT>
        static u8 getRenderableTypeIdOf();
    private:
        friend class RenderTask;
        typedef void (*BeforeDrawCallFunc)(RenderTask&, Shader&);

        struct RenderableTypesInitializer_ {
            template <typename TP, typename T>
            static void f(Renderer2D& renderer);
        };

        struct RenderableTypeCtx_ {
            u16 shader_id;
            u16 vertex_layout_id;
            BeforeDrawCallFunc before_draw_f;
        };

        template <typename RT>
        static void callBeforeDraw_(RenderTask& rt, Shader& s);

        Window* window_;

        RenderableTypeCtx_ rt_ctxs_[config::MAX_RENDERABLE_TYPES];

        std::map< u32 /*render_sorting_id*/, fast_vector<u32> /* task positions */ > to_render_;
    };

}


#include "Renderer2D.inl"
#endif //RENDERER_H
