#include <geng/graphics/Renderables/Renderable.h>
#include "Renderer2D.h"
#include "geng/graphics/Renderables/RenderBatchId.h"
#include "VertexData/VertexData.h"
#include "Shaders/Shader.h"

namespace grynca {

    inline void RenderTask::setRenderableTypeId(u8 rtid) {
        renderable_type_id_ = rtid;
    }

    inline void RenderTask::setZFromLayerId(u16 layer_id) {
        accDrawDataAs<Renderable::DrawData>().z_coord = layerIdToZ_(layer_id);
    }

    inline void RenderTask::setGeom(const VertexData::IRefPtr& g) {
        geom_ref_ = g;
    }

    inline void RenderTask::setTransformMat(const Mat3& tm) {
        accDrawDataAs<Renderable::DrawData>().transform = tm;
    }

    inline const VertexData::IRefPtr& RenderTask::getGeom()const {
        return geom_ref_;
    }

    inline const GeomStateBase& RenderTask::getGeomState()const {
        return getGeom()->getState();
    }

    inline Index RenderTask::getGeomId()const {
        return geom_ref_.getItemId();
    }

    inline const Mat3& RenderTask::getTransformMat()const {
        return getDrawDataAs<Renderable::DrawData>().transform;
    }

    inline u8* RenderTask::getDrawData() {
        return draw_data_;
    }

    inline u8 RenderTask::getRenderableTypeId()const {
        return renderable_type_id_;
    }

    template <typename T>
    inline T& RenderTask::accDrawDataAs() {
        return *(T*)draw_data_;
    }

    template <typename T>
    inline const T& RenderTask::getDrawDataAs()const {
        return *(T*)draw_data_;
    }

    inline u16 RenderTask::getLayerIdFromZ()const {
        return ZToLayerId_(getDrawDataAs<Renderable::DrawData>().z_coord);
    }

    inline GeomStateBase& RenderTask::accGeomState() {
        return accGeom()->accState();
    }

    inline VertexData::IRefPtr& RenderTask::accGeom() {
        return geom_ref_;
    }

    inline Mat3& RenderTask::accTransformMat() {
        return accDrawDataAs<Renderable::DrawData>().transform;
    }

    inline RenderBatchId RenderTask::calcRenderBatchId()const {
        RenderBatchId rslt;
        Renderer2D::RenderableTypeCtx_& rtctx = getManager().rt_ctxs_[renderable_type_id_];
        rslt.setShaderId(rtctx.shader_id);
        rslt.setVertexLayoutId(rtctx.vertex_layout_id);
        rslt.setVertexBufferId(geom_ref_->getVertexBufferId());
        u32 layer_id = ZToLayerId_(getDrawDataAs<Renderable::DrawData>().z_coord);
        rslt.setLayerId(layer_id);

        return rslt;
    }

    inline void RenderTask::cloneTo(RenderTask& rt_out)const {
        memcpy(rt_out.draw_data_, draw_data_, config::DRAW_DATA_SIZE);
        rt_out.renderable_type_id_ = renderable_type_id_;
        rt_out.geom_ref_ = geom_ref_;
    }

    inline f32 RenderTask::layerIdToZ_(u16 layer_id) {
        // static
        // in opengl NDC camera is looking to -z from -1(far) to 0
        // transforms layer id to -0.99 (layer 0) to 0.0 coordinate
        constexpr f32 delta = 0.99f/config::MAX_LAYERS;
        return -0.99f +(layer_id*delta);
    }

    inline u16 RenderTask::ZToLayerId_(f32 z_coord) {
        //static
        constexpr f32 delta_inv = config::MAX_LAYERS/0.99f;
        return u16((z_coord + 0.99f)*delta_inv + 0.1f);
    }

    inline Renderer2D::Renderer2D(Window& w)
     : window_(&w)
    {
    }

    template <typename Types>
    void Renderer2D::initRenderableTypes() {
        Types::template callOnTypes<RenderableTypesInitializer_>(*this);
    }

    inline void Renderer2D::scheduleForNextFrame(Index rt_id, const Mat3& transform_mat, RenderBatchId batch_id) {
        RenderTask& rt = accItem(rt_id);
        rt.setTransformMat(transform_mat);
        to_render_[batch_id.getAsInt()].push_back(getItemPos(rt_id));
    }

    inline void Renderer2D::scheduleForNextFrame(Index rt_id, const Mat3& transform_mat) {
        RenderTask& rt = accItem(rt_id);
        rt.setTransformMat(transform_mat);
        RenderBatchId batch_id = rt.calcRenderBatchId();
        to_render_[batch_id.getAsInt()].push_back(getItemPos(rt_id));
    }

    inline void Renderer2D::render() {
        u16 prev_sid = u16(InvalidId());
        u16 prev_vid = u16(InvalidId());
        u16 prev_bid = u16(InvalidId());
        Shader* shader = NULL;
        VertexData* verts = NULL;

        for (auto it = to_render_.begin(); it != to_render_.end(); ++it) {
            RenderBatchId rid(it->first);
            fast_vector<u32>& rt_positions = it->second;
            if (rt_positions.empty()) {
                continue;
            }
#ifdef DEBUG_BUILD
            u32 batch_id = rid.getAsInt();
            u16 lid = rid.getLayerId();
#endif
            u16 sid = rid.getShaderId();
            if (prev_sid != sid) {
                shader = window_->getShaders().getById(sid);
                shader->bind();
                prev_sid = sid;
            }
            u16 vid = rid.getVertexLayoutId();
            u16 bid = rid.getVertexBufferId();
            if (prev_vid != vid) {
                verts = window_->getVertices().getById(vid);
                verts->bindBufferWithLayouts(bid);
                prev_vid = vid;
                prev_bid = bid;
            }
            else if (prev_bid != bid) {
                verts->bindBufferWithLayouts(bid);
                prev_bid = bid;
            }

            for (u32 i=0; i<rt_positions.size(); ++i) {
                RenderTask& rt = accItemAtPos2(rt_positions[i]);
                Geom& geom = verts->accItem(rt.getGeomId());
                if (geom.getVertsCountVbo() > 0) {
                    rt_ctxs_[rt.getRenderableTypeId()].before_draw_f(rt, *shader);
                    verts->accItem(rt.getGeomId()).render();
                }
            }
            rt_positions.clear();
        }
    }

    inline Window& Renderer2D::getWindow() {
        return *window_;
    }

    template <typename RT>
    inline u8 Renderer2D::getRenderableTypeIdOf() {
        // static
        u32 rt_id = Type<RT, Renderer2D>::getInternalTypeId();
        ASSERT(rt_id < config::MAX_RENDERABLE_TYPES);
        return u8(rt_id);
    }

    template <typename TP, typename RT>
    inline void Renderer2D::RenderableTypesInitializer_::f(Renderer2D &renderer) {
        // static
        ASSERT_M(sizeof(typename RT::DrawData) <= config::DRAW_DATA_SIZE, "Renderable Draw Data too large");
        u8 rend_type_id = Renderer2D::getRenderableTypeIdOf<RT>();

        Renderer2D::RenderableTypeCtx_& rtctx = renderer.rt_ctxs_[rend_type_id];
        rtctx.shader_id = u16(Shaders::getTypeIdOf<typename RT::ShaderType>());
        rtctx.vertex_layout_id = u16(Vertices::getTypeIdOf<typename RT::VertexDataType>());
        rtctx.before_draw_f = Renderer2D::callBeforeDraw_<RT>;
    }

    template <typename RT>
    inline void Renderer2D::callBeforeDraw_(RenderTask& rt, Shader& s) {
        // static
        RT rend;
        rend.setRenderTaskPtr(rt);
        rend.onBeforeDraw(s);
    }
}
