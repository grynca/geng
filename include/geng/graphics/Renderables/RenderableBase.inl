#include "RenderableBase.h"
#include "geng/graphics/Geom.h"
#include "geng/graphics/Window.h"
#include "geng/graphics/Shaders.h"
#include "geng/graphics/VertexData.h"
#include "geng/graphics/Vertices.h"
#include "geng/graphics/graphics_config.h"
#include <cassert>

namespace grynca {

    inline RenderableBase::~RenderableBase() {
    }

    inline void RenderableBase::render() {
        getGeom().render();
    }

    inline Transform& RenderableBase::accLocalTransform() {
        return local_transform_;
    }

    inline bool RenderableBase::getVisible()const {
        return GET_BIT(flags_, fVisible);
    }

    inline void RenderableBase::setVisible(bool value) {
        flags_ = SET_BITV(flags_, fVisible, value);
    }

    inline CoordFrame RenderableBase::getCoordFrame()const {
        return GET_BIT(flags_, fScreenCoordFrame)?CoordFrame::cfScreen:CoordFrame::cfWorld;
    }

    inline void RenderableBase::setCoordFrame(CoordFrame f) {
        flags_ = SET_BITV(flags_, fScreenCoordFrame, f==CoordFrame::cfScreen);
    }

    inline Shader& RenderableBase::getShader()const {
        return *getWindow().getShaders().getById(sorting_key_.shader_id);
    }

    inline VertexData& RenderableBase::getVertexData()const {
        return *getWindow().getVertices().getById(sorting_key_.vertex_layout_id);
    }

    inline Geom& RenderableBase::getGeom()const {
        return geom_ref_.get();
    }

    inline bool RenderableBase::compare(RenderableBase* r1, RenderableBase* r2) {
        //static
        return (r1->sorting_key_.key < r2->sorting_key_.key);
    }

    inline RenderableBase::RenderableBase()
     : flags_((1<<fVisible))
    {
        sorting_key_.layer_id = 0;
        layer_z_ = 0.99f;
    }

    template <typename ShaderType, typename VertexDataType>
    inline void RenderableBase::init(Geom& geom) {
        Window& w = geom.getManager().getManager().getWindow();
        ASSERT_M(geom.getManager().getId() == w.getVertices().get<VertexDataType>().getId(),
               "Geom not compatible with needed vertex data.");
        geom_ref_ = geom;
        sorting_key_.shader_id = w.getShaders().get<ShaderType>().getId();
        sorting_key_.vertex_layout_id = w.getVertices().get<VertexDataType>().getId();
    };

    inline Window& RenderableBase::getWindow()const {
        return getGeom().getManager().getManager().getWindow();
    }

    inline Shader& RenderableBase::getShaderInner(Window& w)const {
        return *w.getShaders().getById(sorting_key_.shader_id);
    }

    inline VertexData& RenderableBase::getVertexDataInner(Window& w)const {
        return *w.getVertices().getById(sorting_key_.vertex_layout_id);
    }

    inline uint16_t RenderableBase::getLayerId()const {
        return sorting_key_.layer_id;
    }

    inline void RenderableBase::setLayerId(uint16_t layer_id) {
        sorting_key_.layer_id = layer_id;
        layer_z_ = calcLayerZ_(layer_id);
    }

    template <typename ShaderType>
    inline void RenderableBase::setShader() {
        sorting_key_.shader_id = getWindow().getShaders().get<ShaderType>().getId();
    }

    template <typename VertexDataType>
    inline void RenderableBase::setVertexLayout() {
        sorting_key_.vertex_layout_id = getWindow().getVertices().get<VertexDataType>().getId();
    }

    inline float RenderableBase::calcLayerZ_(uint32_t layer_id) {
        // in opengl NDC camera is looking to -z from -1(far) to 0
        // transforms layer id to 0.99 (layer 0) to 0.0 coordinate
        static float delta = 0.99f/config::MAX_LAYERS;
        return 0.99f -(layer_id*delta);
    }

}