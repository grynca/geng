#include "Renderable.h"
#include "Geom.h"
#include "Window.h"
#include "Shaders.h"
#include "VertexData.h"
#include "Vertices.h"
#include "graphics_config.h"
#include <cassert>

namespace grynca {

    inline Renderable::~Renderable() {

    }

    inline void Renderable::render() {
        if (!visible_)
            return;
        getShader().bind();
        getVertexData().bind();
        preRender();
        getGeom().render();
    }

    inline Transform& Renderable::getLocalTransform() {
        return local_transform_;
    }

    inline void Renderable::setMVP(const Mat3& mvp) {
        mvp_ = mvp;
    }

    inline const Mat3& Renderable::getMVP()const {
        return mvp_;
    }

    inline bool Renderable::getVisible()const {
        return visible_;
    }

    inline void Renderable::setVisible(bool value) {
        visible_ = value;
    }

    inline CoordFrame Renderable::getCoordFrame()const {
        return coord_frame_;
    }

    inline void Renderable::setCoordFrame(CoordFrame f) {
        coord_frame_ = f;
    }

    inline Window& Renderable::getWindow()const {
        return *window_;
    }

    inline Shader& Renderable::getShader()const {
        return *window_->getShaders().getById(sorting_key_.shader_id);
    }

    inline VertexData& Renderable::getVertexData()const {
        return *window_->getVertices().getById(sorting_key_.vertex_layout_id);
    }

    inline Geom& Renderable::getGeom()const {
        return geom_ref_.get();
    }

    inline bool Renderable::compare(Renderable* r1, Renderable* r2) {
        //static
        return (r1->sorting_key_.key < r2->sorting_key_.key);
    }

    inline Renderable::Renderable()
     : window_(NULL), visible_(true), coord_frame_(cfWorld)
    {
        sorting_key_.layer_id = 0;
        layer_z_ = 0.99f;
    }

    template <typename ShaderType, typename VertexDataType>
    inline void Renderable::init(Geom& geom) {
        window_ = &geom.getManager().getManager().getWindow();
        ASSERT(geom.getManager().getId() == window_->getVertices().get<VertexDataType>().getId(),
               "Geom not compatible with needed vertex data.");
        geom_ref_ = geom;
        sorting_key_.shader_id = window_->getShaders().get<ShaderType>().getId();
        sorting_key_.vertex_layout_id = window_->getVertices().get<VertexDataType>().getId();
    };

    inline uint16_t Renderable::getLayerId()const {
        return sorting_key_.layer_id;
    }

    inline void Renderable::setLayerId(uint16_t layer_id) {
        sorting_key_.layer_id = layer_id;
        layer_z_ = calcLayerZ_(layer_id);
    }

    inline float Renderable::calcLayerZ_(uint32_t layer_id) {
        // in opengl NDC camera is looking to -z from -1(far) to 0
        // transforms layer id to 0.99 (layer 0) to 0.0 coordinate
        static float delta = 0.99f/config::MAX_LAYERS;
        return 0.99f -(layer_id*delta);
    }

}