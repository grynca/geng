#include "SpriteAnimationStates.h"
#include "../Vertices.h"

namespace grynca {

    inline SpriteAnimationStates::SpriteAnimationStates(SpriteAnimations& anims)
     : anims_(&anims)
    {
    }

    inline SpriteAnimationState::SpriteAnimationState()
     : curr_frame_(InvalidId()), to_next_frame_(0.0f), geom_id_(Index::Invalid()), anim_id_(Index::Invalid())
    {
    }

    inline u32 SpriteAnimationState::getCurrFrameId()const {
        return curr_frame_;
    }

    inline bool SpriteAnimationState::isFirstFrame()const {
        return curr_frame_ == 0;
    }

    inline bool SpriteAnimationState::isLastFrame()const {
        return curr_frame_ == getAnimation().getFramesCount()-1;
    }

    inline bool SpriteAnimationState::isPaused()const {
        return flags_[fPaused];
    }

    inline bool SpriteAnimationState::isForward()const {
        return !flags_[fBackwards];
    }

    inline SpriteAnimationState::EndAction SpriteAnimationState::getEndAction()const {
        if (flags_[fAutoChangeDir])
            return eaChangeDir;
        if (flags_[fWrapAround])
            return eaWrapAround;
        return eaStop;
    }

    inline f32 SpriteAnimationState::getTimeToNextFrame()const {
        return to_next_frame_;
    }

    inline SpriteAnimation& SpriteAnimationState::getAnimation()const {
        return getManager().anims_->getItem(anim_id_);
    }

    inline SpriteAnimationFrame& SpriteAnimationState::getCurrFrame()const {
        return getAnimation().getFrame(curr_frame_);
    }

    inline Index SpriteAnimationState::getGeomId()const {
        return geom_id_;
    }

    inline SpriteAnimationState& SpriteAnimationState::flipDirection() {
        flags_[fBackwards] = !flags_[fBackwards];
        to_next_frame_ = getCurrFrame().getTime() - to_next_frame_;
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setEndAction(EndAction ea) {
        switch (ea) {
            case eaChangeDir:
                flags_[fAutoChangeDir] = 1;
                flags_[fWrapAround] = 0;
                break;
            case eaWrapAround:
                flags_[fWrapAround] = 1;
                flags_[fAutoChangeDir] = 0;
                break;
            case eaStop:
                flags_[fWrapAround] = 0;
                flags_[fAutoChangeDir] = 0;
                break;
        }
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setPaused(bool val) {
        flags_[fPaused] = val;
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setCurrFrameId(u32 f_id) {
        if (curr_frame_ != f_id) {
            curr_frame_ = f_id;
            SpriteAnimationFrame& new_frame = getCurrFrame();
            to_next_frame_ = new_frame.getTime();
            flags_.set(fFrameChanged);
        }
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setToFirstFrame() {
        return setCurrFrameId(0);
    }

    inline SpriteAnimationState& SpriteAnimationState::setToLastFrame() {
        return setCurrFrameId(getAnimation().getFramesCount() -1);
    }

    inline SpriteAnimationState& SpriteAnimationState::setTimeToNextFrame(f32 tnf) {
        to_next_frame_ = tnf;
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setForward(bool value) {
        flags_[fBackwards] = !value;
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setGeomId(Index geom_id) {
        geom_id_ = geom_id;
        return *this;
    }

    inline SpriteAnimationState& SpriteAnimationState::setAnimationId(Index anim_id) {
        anim_id_ = anim_id;
        return setToFirstFrame();
    }

    inline bool SpriteAnimationState::advanceAnimation(f32 dt) {
        bool changed = flags_[fFrameChanged];
        flags_.reset(fFrameChanged);

        to_next_frame_ -= dt;
        if (to_next_frame_ < 0.0f) {
            // change frame
            if (isForward()) {
                if (curr_frame_ == (getAnimation().getFramesCount()-1)) {
                    switch (getEndAction()) {
                        case SpriteAnimationState::eaStop:
                            to_next_frame_ = 0;
                            setPaused(true);
                            return changed;
                        case SpriteAnimationState::eaChangeDir:
                            flipDirection();
                            return changed;
                        case SpriteAnimationState::eaWrapAround:
                            curr_frame_ = 0;
                            break;
                    }
                }
                else {
                    ++curr_frame_;
                }
            } else {
                if (curr_frame_ == 0) {
                    switch (getEndAction()) {
                        case SpriteAnimationState::eaStop:
                            to_next_frame_ = 0;
                            setPaused(true);
                            return changed;;
                        case SpriteAnimationState::eaChangeDir:
                            flipDirection();
                            return changed;;
                        case SpriteAnimationState::eaWrapAround:
                            curr_frame_ = getAnimation().getFramesCount() - 1;
                            break;
                    }
                }
                else {
                    --curr_frame_;
                }
            }

            changed = true;
            SpriteAnimationFrame& f = getAnimation().getFrame(curr_frame_);
            to_next_frame_ += f.getTime();
        }
        return changed;
    }

}