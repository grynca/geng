#include "SpriteRenderable.h"
#include "assets.h"
#include "../geom_utils.h"
#include "../VertexData/VertexDataPT.h"
#include "../Shaders/SpriteShader.h"

namespace grynca {

    inline SpriteRenderable::SpriteRenderable()
        : assets_(NULL), texture_unit_(0), animation_id_(uint32_t(-1))
    {
    }

    template <typename GameType>
    inline SpriteRenderable& SpriteRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id) {
        AssetsManager& assets = game.template getModule<AssetsManager>();
        const TextureRegion& first_frame_reg = assets.getAnimations().getItem(animation_id).getFrame(0).getRegion();
        return init(game, layer_id, texture_unit, animation_id, first_frame_reg.getRect().getSize(), first_frame_reg.getRect().getSize()/-2);
    }

    template <typename GameType>
    inline SpriteRenderable& SpriteRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id, const Vec2& size) {
        return init(game, layer_id, texture_unit, animation_id, size, size/-2);
    }

    template <typename GameType>
    inline SpriteRenderable& SpriteRenderable::init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id, const Vec2& size, const Vec2& offset) {
        assets_ = &game.template getModule<AssetsManager>();
        texture_unit = texture_unit_;
        animation_id_ = animation_id;
        Window& window = game.template getModule<Window>();
        AnimationFrame& first_frame = assets_->getAnimations().getItem(animation_id_).getFrame(0);
        Geom& geom = window.getVertices().get<VertexDataPT>().addItem(GL_TRIANGLE_FAN);
        geom_utils::RectTF::add<VertexDataPT::Vertex>(geom);
        geom_utils::RectTF::setSize<VertexDataPT::Vertex>(geom, 0, size);
        geom_utils::RectTF::setOffset<VertexDataPT::Vertex>(geom, 0, offset);
        const ARect& r =first_frame.getRegion().getTextureRect();
        geom_utils::RectTF::setTC<VertexDataPT::Vertex>(geom, 0, r.getLeftTop(), r.getRightBot());
        Renderable::init<SpriteShader, VertexDataPT>(geom, layer_id);

        curr_frame_ = 0;
        to_next_frame_ = first_frame.getTime();

        return *this;
    }

    inline void SpriteRenderable::setAnimationId(uint32_t animation_id) {
        animation_id_ = animation_id;
        setFrameId(0);
    }

    inline int32_t SpriteRenderable::getFrameId()const {
        return curr_frame_;
    }

    inline bool SpriteRenderable::isFirstFrame()const {
        return curr_frame_ == 0;
    }

    inline bool SpriteRenderable::isLastFrame()const {
        Animation &a = assets_->getAnimations().getItem(animation_id_);
        return curr_frame_ == a.getFramesCount()-1;
    }

    inline void SpriteRenderable::setToFirstFrame() {
        setFrameId(0);
    }

    inline void SpriteRenderable::setToLastFrame() {
        Animation &a = assets_->getAnimations().getItem(animation_id_);
        setFrameId(a.getFramesCount()-1);
    }

    inline Animation& SpriteRenderable::getAnimation() {
        return assets_->getAnimations().getItem(animation_id_);
    }

    inline float SpriteRenderable::getToNextFrame()const {
        return to_next_frame_;
    }

    inline void SpriteRenderable::setFrameId(uint32_t f_id) {
        AnimationFrame& f = assets_->getAnimations().getItem(animation_id_).getFrame(f_id);
        curr_frame_ = f_id;
        to_next_frame_ = f.getTime();
        const ARect& r = f.getRegion().getTextureRect();
        geom_utils::RectTF::setTC<VertexDataPT::Vertex>(getGeom(), 0, r.getLeftTop(), r.getRightBot());
    }

    inline void SpriteRenderable::setToNextFrame(float tnf) {
        to_next_frame_ = tnf;
    }

    inline void SpriteRenderable::changeDirection() {
        flags_[0] = !flags_[0];
    }

    inline bool SpriteRenderable::isGoingBackward()const {
        return flags_[0];
    }

    inline bool SpriteRenderable::isGoingForward()const {
        return !isGoingBackward();
    }

    inline bool SpriteRenderable::getWrapAround()const {
        return flags_[1];
    }

    inline void SpriteRenderable::setWrapAround(bool val) {
        flags_[1] = val;
    }

    inline bool SpriteRenderable::isPaused()const {
        return flags_[2];
    }

    inline void SpriteRenderable::setPaused(bool val) {
        flags_[2] = val;
    }

    inline bool SpriteRenderable::getAutoChangeDir()const {
        return flags_[3];
    }

    inline void SpriteRenderable::setAutoChangeDir(bool val) {
        flags_[3] = val;
    }

    inline bool SpriteRenderable::getFrameChanged()const {
        return flags_[4];
    }

    inline AssetsManager& SpriteRenderable::getAssets() {
        return *assets_;
    }

    inline void SpriteRenderable::advanceAnimation(float dt) {
        flags_[4] = false;
        float tnf = to_next_frame_;
        to_next_frame_ -= dt;
        if (tnf <= 0.0f) {
            Animation &a = assets_->getAnimations().getItem(animation_id_);
            int32_t cf = curr_frame_;
            if (isGoingForward()) {
                ++cf;
                if (cf >= a.getFramesCount()) {
                    if (getAutoChangeDir()) {
                        changeDirection();
                        --cf;
                    }
                    else if (getWrapAround()) {
                        cf = 0;
                    }
                    else {
                        setPaused(true);
                        return;
                    }
                }
            }
            else {
                --cf;
                if (cf < 0) {
                    if (getAutoChangeDir()) {
                        changeDirection();
                        ++cf;
                    }
                    else if (getWrapAround()) {
                        cf = a.getFramesCount() - 1;
                    }
                    else {
                        setPaused(true);
                        return;
                    }
                }
            }
            AnimationFrame &f = a.getFrame((uint32_t)cf);
            if (curr_frame_ != cf) {
                const ARect& r = f.getRegion().getTextureRect();
                geom_utils::RectTF::setTC<VertexDataPT::Vertex>(getGeom(), 0, r.getLeftTop(), r.getRightBot());
                curr_frame_ = cf;
                flags_[4] = true;
            }
            to_next_frame_ = f.getTime();
        }
    }

    inline uint32_t SpriteRenderable::getTextureUnit()const {
        return texture_unit_;
    }

    inline void SpriteRenderable::setTextureUnit(uint32_t tid) {
        texture_unit_ = tid;
    }

    inline Vec2 SpriteRenderable::getSize() {
        return geom_utils::RectTF::getSize<VertexDataPT::Vertex>(getGeom(), 0);
    }

    inline Vec2 SpriteRenderable::getOffset() {
        return geom_utils::RectTF::getOffset<VertexDataPT::Vertex>(getGeom(), 0);
    }

    inline void SpriteRenderable::setSize(const Vec2& size) {
        geom_utils::RectTF::setSize<VertexDataPT::Vertex>(getGeom(), 0, size);
    }

    inline void SpriteRenderable::setOffset(const Vec2& offset) {
        geom_utils::RectTF::setOffset<VertexDataPT::Vertex>(getGeom(), 0, offset);
    }

    inline void SpriteRenderable::preRender() {
        SpriteShader& ss = (SpriteShader&)getShader();

        ss.setUniformMat3(ss.u_transform, mvp_);
        ss.setUniform1f(ss.u_z_coord, layer_z_);
        ss.setUniform1i(ss.u_texture, texture_unit_);
    }
}