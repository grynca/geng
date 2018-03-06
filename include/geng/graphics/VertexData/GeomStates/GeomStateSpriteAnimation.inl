#include "GeomStateSpriteAnimation.h"
#include "geng/graphics/Vertices.h"

namespace grynca {

    inline GeomStateSpriteAnimation::GeomStateSpriteAnimation(GeomStateType type_id, VertexData& vd, Index geom_id)
     : GeomStateBase(type_id, vd, geom_id),
       curr_frame_(InvalidId()), to_next_frame_(0.0f)
    {
    }

    inline u32 GeomStateSpriteAnimation::getCurrFrameId()const {
        return curr_frame_;
    }

    inline bool GeomStateSpriteAnimation::isFirstFrame()const {
        return curr_frame_ == 0;
    }

    inline bool GeomStateSpriteAnimation::isLastFrame()const {
        return curr_frame_ == getAnimation()->getFramesCount()-1;
    }

    inline bool GeomStateSpriteAnimation::isPaused()const {
        return flags_[fPaused];
    }

    inline bool GeomStateSpriteAnimation::isForward()const {
        return !flags_[fBackwards];
    }

    inline GeomStateSpriteAnimation::EndAction GeomStateSpriteAnimation::getEndAction()const {
        if (flags_[fAutoChangeDir])
            return eaChangeDir;
        if (flags_[fWrapAround])
            return eaWrapAround;
        return eaStop;
    }

    inline f32 GeomStateSpriteAnimation::getTimeToNextFrame()const {
        return to_next_frame_;
    }

    inline const SpriteAnimations::IRefPtr& GeomStateSpriteAnimation::getAnimation()const {
        return animation_;
    }

    inline const SpriteAnimationFrame& GeomStateSpriteAnimation::getCurrFrame()const {
        return getAnimation()->getFrame(curr_frame_);
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::flipDirection() {
        flags_[fBackwards] = !flags_[fBackwards];
        to_next_frame_ = getCurrFrame().getTime() - to_next_frame_;
        return *this;
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setEndAction(EndAction ea) {
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

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setPaused(bool val) {
        flags_[fPaused] = val;
        return *this;
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setCurrFrameId(u32 f_id) {
        if (curr_frame_ != f_id) {
            curr_frame_ = f_id;
            const SpriteAnimationFrame& new_frame = getCurrFrame();
            to_next_frame_ = new_frame.getTime();
            flags_.set(fFrameChanged);
        }
        return *this;
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setToFirstFrame() {
        return setCurrFrameId(0);
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setToLastFrame() {
        return setCurrFrameId(getAnimation()->getFramesCount() -1);
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setTimeToNextFrame(f32 tnf) {
        to_next_frame_ = tnf;
        return *this;
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setForward(bool value) {
        flags_[fBackwards] = !value;
        return *this;
    }

    inline GeomStateSpriteAnimation& GeomStateSpriteAnimation::setAnimation(const SpriteAnimations::IRefPtr& anim) {
        animation_ = anim;
        return setToFirstFrame();
    }

    inline bool GeomStateSpriteAnimation::advanceAnimation(f32 dt) {
        bool changed = flags_[fFrameChanged];
        flags_.reset(fFrameChanged);

        to_next_frame_ -= dt;
        if (to_next_frame_ < 0.0f) {
            // change frame
            if (isForward()) {
                if (curr_frame_ == (getAnimation()->getFramesCount()-1)) {
                    switch (getEndAction()) {
                        case GeomStateSpriteAnimation::eaStop:
                            to_next_frame_ = 0;
                            setPaused(true);
                            return changed;
                        case GeomStateSpriteAnimation::eaChangeDir:
                            flipDirection();
                            return changed;
                        case GeomStateSpriteAnimation::eaWrapAround:
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
                        case GeomStateSpriteAnimation::eaStop:
                            to_next_frame_ = 0;
                            setPaused(true);
                            return changed;;
                        case GeomStateSpriteAnimation::eaChangeDir:
                            flipDirection();
                            return changed;;
                        case GeomStateSpriteAnimation::eaWrapAround:
                            curr_frame_ = getAnimation()->getFramesCount() - 1;
                            break;
                    }
                }
                else {
                    --curr_frame_;
                }
            }

            changed = true;
            const SpriteAnimationFrame& f = getAnimation()->getFrame(curr_frame_);
            to_next_frame_ += f.getTime();
        }
        return changed;
    }

}