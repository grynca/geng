#include "SpriteRenderable.h"
#include "assets.h"
#include "../VertexData/VertexDataPT.h"
#include "../Shaders/SpriteShader.h"
#include "../geom_factories.h"

namespace grynca {

    template <typename GameType>
    inline SpriteRenderable::SpriteRenderable(GameType& game)
        : assets_(&game.template getModule<AssetsManager>()), texture_unit_(0)
    {
        Window& window = game.template getModule<Window>();
        FactoryRectTF<VertexDataPT::Vertex> fact = window.getVertices().get<VertexDataPT>().addWithFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        Renderable::init<SpriteShader, VertexDataPT>(fact.getGeom());
    }

    template <typename GameType>
    inline SpriteRenderable::SpriteRenderable(GameType& game, Geom& geom)
     : assets_(&game.template getModule<AssetsManager>()), texture_unit_(0)
    {
        Renderable::init<SpriteShader, VertexDataPT>(geom);
    }

    inline SpriteRenderable& SpriteRenderable::setImageRegion(const TextureRegion& tr, const Vec2& offset) {
        setImageRegion(tr.getTextureRect(), tr.getRect().getSize(), offset);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setImageRegion(const ARect& texture_coords, const Vec2& base_size, const Vec2& offset) {
        animation_state_.animation_id = Index::Invalid();
        FactoryRectTF<VertexDataPT::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.setTC(0, texture_coords.getLeftTop(), texture_coords.getRightBot());
        fact.setSize(0, base_size);
        fact.setOffset(0, base_size*offset);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setAnimation(uint32_t animation_id) {
        animation_state_.animation_id = animation_id;
        setFrameId(0);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setFrameId(uint32_t f_id) {
        AnimationFrame& f = assets_->getAnimations().getItem(animation_state_.animation_id).getFrame(f_id);
        animation_state_.curr_frame = f_id;
        animation_state_.to_next_frame = f.getTime();
        setFrameInternal_(f);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setToFirstFrame() {
        setFrameId(0);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setToLastFrame() {
        Animation &a = assets_->getAnimations().getItem(animation_state_.animation_id);
        setFrameId(a.getFramesCount()-1);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setTimeToNextFrame(float tnf) {
        animation_state_.to_next_frame = tnf;
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setPaused(bool val) {
        animation_state_.flags[AnimationState::fPaused] = val;
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setDirection(Direction dir) {
        animation_state_.flags[AnimationState::fBackwards] = (dir==dBackward);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::flipDirection() {
        animation_state_.flags[AnimationState::fBackwards] = !animation_state_.flags[AnimationState::fBackwards];
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setEndAction(EndAction a) {
        switch (a) {
            case eaChangeDir:
                animation_state_.flags[AnimationState::fAutoChangeDir] = 1;
                animation_state_.flags[AnimationState::fWrapAround] = 0;
                break;
            case eaWrapAround:
                animation_state_.flags[AnimationState::fWrapAround] = 1;
                animation_state_.flags[AnimationState::fAutoChangeDir] = 0;
                break;
            case eaStop:
                animation_state_.flags[AnimationState::fWrapAround] = 0;
                animation_state_.flags[AnimationState::fAutoChangeDir] = 0;
                break;
        }
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setTextureUnit(uint32_t tid) {
        texture_unit_ = tid;
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setSize(const Vec2& size) {
        Vec2 base_size = getBaseSize();
        Vec2 scale = size/base_size;
        getLocalTransform().setScale(scale);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setOffset(const Vec2& offset) {
        getGeom().getFactory<FactoryRectTF<VertexDataPT::Vertex> > ().setOffset(0, getBaseSize()*offset);
        return *this;
    }

    inline bool SpriteRenderable::isImage()const {
        return animation_state_.animation_id == Index::Invalid();
    }

    inline bool SpriteRenderable::isAnimation()const {
        return animation_state_.animation_id != Index::Invalid();
    }

    inline bool SpriteRenderable::isFirstFrame()const {
        return animation_state_.curr_frame == 0;
    }

    inline bool SpriteRenderable::isLastFrame()const {
        Animation &a = assets_->getAnimations().getItem(animation_state_.animation_id);
        return animation_state_.curr_frame == (a.getFramesCount()-1);
    }

    inline bool SpriteRenderable::isPaused()const {
        return animation_state_.flags[AnimationState::fPaused];
    }

    inline AssetsManager& SpriteRenderable::getAssets()const {
        return *assets_;
    }

    inline Animation& SpriteRenderable::getAnimation()const {
        return assets_->getAnimations().getItem(animation_state_.animation_id);
    }

    inline int32_t SpriteRenderable::getFrameId()const {
        return animation_state_.curr_frame;
    }

    inline AnimationFrame& SpriteRenderable::getFrame()const {
        Animation &a = assets_->getAnimations().getItem(animation_state_.animation_id);
        return a.getFrame(uint32_t(animation_state_.curr_frame));
    }

    inline float SpriteRenderable::getTimeToNextFrame()const {
        return animation_state_.to_next_frame;
    }

    inline SpriteRenderable::Direction SpriteRenderable::getDirection()const {
        return animation_state_.flags[AnimationState::fBackwards]?dBackward:dForward;
    }

    inline SpriteRenderable::EndAction SpriteRenderable::getEndAction()const {
        if (animation_state_.flags[AnimationState::fAutoChangeDir])
            return eaChangeDir;
        if (animation_state_.flags[AnimationState::fWrapAround])
            return eaWrapAround;
        return eaStop;
    }

    inline bool SpriteRenderable::getFrameChanged()const {
        return animation_state_.flags[AnimationState::fFrameChanged];
    }

    inline uint32_t SpriteRenderable::getTextureUnit()const {
        return texture_unit_;
    }

    inline Vec2 SpriteRenderable::getSize()const {
        return getBaseSize()*local_transform_.getScale();
    }

    inline Vec2 SpriteRenderable::getBaseSize()const {
        return getGeom().getFactory<FactoryRectTF<VertexDataPT::Vertex> > ().getSize(0);
    }

    inline Vec2 SpriteRenderable::getOffset()const {
        return getBaseOffset()/getSize();
    }

    inline Vec2 SpriteRenderable::getBaseOffset()const {
        return getGeom().getFactory<FactoryRectTF<VertexDataPT::Vertex> > ().getOffset(0);
    }

    inline void SpriteRenderable::advanceAnimation(float dt) {
        animation_state_.flags[AnimationState::fFrameChanged] = false;
        float tnf = animation_state_.to_next_frame;
        animation_state_.to_next_frame -= dt;
        if (tnf <= 0.0f) {
            Animation &a = assets_->getAnimations().getItem(animation_state_.animation_id);
            int32_t cf = animation_state_.curr_frame;
            if (getDirection() == dForward) {
                ++cf;
                if (cf >= a.getFramesCount()) {
                    switch (getEndAction()) {
                        case eaChangeDir:
                            flipDirection();
                            --cf;
                            break;
                        case eaWrapAround:
                            cf = 0;
                            break;
                        case eaStop:
                            setPaused(true);
                            return;
                    }
                }
            }
            else {
                --cf;
                if (cf < 0) {
                    switch (getEndAction()) {
                        case eaChangeDir:
                            flipDirection();
                            ++cf;
                            break;
                        case eaWrapAround:
                            cf = a.getFramesCount() - 1;
                            break;
                        case eaStop:
                            setPaused(true);
                            return;
                    }
                }
            }
            AnimationFrame &f = a.getFrame((uint32_t)cf);
            if (animation_state_.curr_frame != cf) {
                const ARect& r = f.getRegion().getTextureRect();
                setFrameInternal_(f);
                animation_state_.curr_frame = cf;
                animation_state_.flags[AnimationState::fFrameChanged] = true;
            }
            animation_state_.to_next_frame = f.getTime();
        }
    }

    inline void SpriteRenderable::preRender() {
        SpriteShader& ss = (SpriteShader&)getShader();

        ss.setUniformMat3(ss.u_transform, mvp_);
        ss.setUniform1f(ss.u_z_coord, layer_z_);
        ss.setUniform1i(ss.u_texture, texture_unit_);
    }

    inline void SpriteRenderable::setFrameInternal_(const AnimationFrame& frame) {
        const ARect& tr = frame.getRegion().getTextureRect();
        FactoryRectTF<VertexDataPT::Vertex> fact = getGeom().getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        Vec2 prev_base_size = fact.getSize(0);
        Vec2 offset = fact.getOffset(0)/prev_base_size;
        Vec2 new_base_size = frame.getRegion().getRect().getSize();
        fact.setSize(0, new_base_size);
        fact.setOffset(0, new_base_size*offset);
        fact.setTC(0, tr.getLeftTop(), tr.getRightBot());
    }
}