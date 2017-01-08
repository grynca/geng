#include "Renderer2D.h"
#include "Renderables/RenderIndex.h"
#include "VertexData/VertexData.h"
#include "Shader.h"

namespace grynca {

    inline RenderTask::RenderTask()
     : coord_frame_(cfWorldLocal)
    {
    }

    inline void RenderTask::setTransform(const Mat3& tm) {
        Shader::UniformsBase* ub = (Shader::UniformsBase*)uniforms_;
        ub->transform = tm;
    }

    inline void RenderTask::setLayer(u16 layer_id) {
        rid_.setLayerId(layer_id);
        Shader::UniformsBase* ub = (Shader::UniformsBase*)uniforms_;
        ub->z_coord = calcLayerZ_(layer_id);
    }

    inline void RenderTask::setCoordFrame(CoordFrame cf) {
        coord_frame_ = cf;
    }

    inline void RenderTask::setGeom(const VertexData::ItemRef& g) {
        geom_ref_ = g;
    }

    inline const VertexData::ItemRef& RenderTask::getGeom()const {
        return geom_ref_;
    }

    inline Index RenderTask::getGeomId()const {
        return geom_ref_.getItemId();
    }

    inline CoordFrame RenderTask::getCoordFrame()const {
        return coord_frame_;
    }

    inline const RenderIndex& RenderTask::getRenderIndex()const {
        return rid_;
    }

    inline const Transform& RenderTask::getLocalTransform()const {
        return local_transform_;
    }

    inline Transform& RenderTask::accLocalTransform() {
        return local_transform_;
    }

    inline RenderIndex& RenderTask::accRenderIndex() {
        return rid_;
    }

    inline VertexData::ItemRef& RenderTask::accGeom() {
        return geom_ref_;
    }

    template <typename T>
    inline T& RenderTask::getUniformsAs() {
        return *(T*)uniforms_;
    }

    template <typename T>
    inline const T& RenderTask::getUniformsAs()const {
        return *(T*)uniforms_;
    }

    inline void RenderTask::calcTransform(Window& window, const Mat3& obj_tr_m) {
        ViewPort& vp = window.getViewPort();
        Shader::UniformsBase& unis = getUniformsAs<Shader::UniformsBase>();
        switch (coord_frame_) {
            case cfScreenLocal:
                // translate 0,0 to left-top corner from center
                unis.transform = vp.getProjectionTransform()
                                 * Mat3::createTranslationT(-0.5f*vp.getBaseSize())
                                 * obj_tr_m * local_transform_.calcMatrix();
                break;
            case cfScreenGlobal:
                unis.transform = vp.getProjectionTransform()
                                 * Mat3::createTranslationT(-0.5f*vp.getBaseSize())
                                 * local_transform_.calcMatrix();
                break;
            case cfWorldLocal:
                unis.transform = vp.getProjectionTransform()
                                 * vp.getViewTransform()
                                 * obj_tr_m * local_transform_.calcMatrix();
                break;
            case cfWorldGlobal:
                unis.transform = vp.getProjectionTransform()
                                 * vp.getViewTransform()
                                 * local_transform_.calcMatrix();
                break;
        }
    }

    inline void RenderTask::setTransformMatrix(const Mat3& mat) {
        Shader::UniformsBase& unis = getUniformsAs<Shader::UniformsBase>();
        unis.transform = mat;
    }

    inline f32 RenderTask::calcLayerZ_(u32 layer_id) {
        // static
        // in opengl NDC camera is looking to -z from -1(far) to 0
        // transforms layer id to -0.99 (layer 0) to 0.0 coordinate
        static f32 delta = 0.99f/config::MAX_LAYERS;
        return -0.99f +(layer_id*delta);
    }

    inline Renderer2D::Renderer2D(Window& w)
     : window_(&w)
    {
    }

    inline void Renderer2D::scheduleForNextFrame(Index rt_id) { ;
        u32 rid_int = getItem(rt_id).getRenderIndex().getAsInt();
        to_render_[rid_int].push_back(getItemPos(rt_id));
    }

    inline void Renderer2D::render() {
        u16 prev_sid = u16(InvalidId());
        u16 prev_vid = u16(InvalidId());
        u16 prev_bid = u16(InvalidId());
        Shader* shader = NULL;
        VertexData* verts = NULL;

        for (auto it = to_render_.begin(); it != to_render_.end(); ++it) {
            RenderIndex rid(it->first);

            if (!rid.getVisible()) {
                fast_vector<u32>& poss = it->second;
                poss.clear();
                break;
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

            fast_vector<u32>& poss = it->second;
            for (u32 i=0; i<poss.size(); ++i) {
                RenderTask& rt = getItemAtPos2(poss[i]);
                shader->setUniforms(rt.getUniformsData());
                verts->getItem(rt.getGeomId()).render();
            }
            poss.clear();
        }
    }

    inline Window& Renderer2D::getWindow() {
        return *window_;
    }
}
