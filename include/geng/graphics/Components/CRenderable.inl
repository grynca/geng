#include "CRenderable.h"

namespace grynca {

    inline CRenderable::CRenderable()
     : dirty_(false)
    {}

    inline CRenderable::~CRenderable() {
        if (dirty_) {
            CRenderableData* data = getData<CRenderableData>();
            const Renderable& rend = renderable_.getBase<Renderable>();
            if (rend.getRenderBatchIdDirty()) {
                // update cached render batch id
                data->render_batch_id = rend.getRenderTaskPtr()->calcRenderBatchId();
            }
            u16 aux_id = data->render_task_id.getAuxIndex();   // preserve aux_id (screen frame flag)
            data->render_task_id = rend.getRenderTaskPtr().getItemId();
            data->render_task_id.setAuxIndex(aux_id);
        }
    }

    template <typename RenderableType>
    inline RenderableType* CRenderable::initR() {
        dirty_ = true;
        Renderer2D::IPtr render_task_ptr = getRendererSingleton_().addItem();

        RenderableType& r = renderable_.create<RenderableType>();
        r.template init<RenderableType>(render_task_ptr);
        return &r;
    }

    template <typename RenderableType>
    inline RenderableType* CRenderable::initRCloned(const Renderer2D::IPtr& render_task) {
        dirty_ = true;
        RenderableType& r = renderable_.create<RenderableType>();
        r.clone(render_task);
        return &r;
    }

    template <typename RenderableType>
    inline RenderableType* CRenderable::changeR() {
        dirty_ = true;
        CRenderableData* data = getData<CRenderableData>();
        Renderer2D::IPtr render_task_ptr = getRendererSingleton_().accItem(data->render_task_id);

        RenderableType& r = renderable_.set<RenderableType>();
        r.template init<RenderableType>(render_task_ptr);
        return &r;
    }

    template <typename RenderableType>
    inline const RenderableType* CRenderable::getR() {
        CRenderableData* data = getData<CRenderableData>();
        Renderer2D::IPtr render_task_ptr = getRendererSingleton_().accItem(data->render_task_id);

        RenderableType& r = renderable_.set<RenderableType>();
        r.setRenderTaskPtr(render_task_ptr);
        return &r;
    }

    template <typename RenderableType>
    inline RenderableType* CRenderable::accR() {
        dirty_ = true;
        return const_cast<RenderableType*>(getR<RenderableType>());
    }

    inline void CRenderable::setScreenFrame(bool val) {
        getData<CRenderableData>()->setScreenFrame(val);
    }

    inline void CRenderable::setLocalTransform(const Transform& tr) {
        getData<CRenderableData>()->local_transform = tr;
    }

    inline const Transform& CRenderable::getLocalTransform()const {
        return getData<CRenderableData>()->local_transform;
    }

    inline Index CRenderable::getRenderTaskId()const {
        return getData<CRenderableData>()->render_task_id;
    }

    inline bool CRenderable::getScreenFrame()const {
        return getData<CRenderableData>()->getScreenFrame();
    }

    inline Transform& CRenderable::accLocalTransform() {
        return getData<CRenderableData>()->local_transform;
    }

    inline Renderer2D& CRenderable::getRendererSingleton_() {
        return GameBase::get().getModule<Window>().getRenderer();
    }
}