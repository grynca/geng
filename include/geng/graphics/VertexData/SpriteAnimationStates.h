#ifndef SPRITE_ANIMATION_STATES_H
#define SPRITE_ANIMATION_STATES_H

#include "types/Manager.h"
#include "assets.h"

namespace grynca {

    // fw
    class SpriteAnimationState;

    class SpriteAnimationStates : public TightManager<SpriteAnimationState> {
    public:
        SpriteAnimationStates(SpriteAnimations& anims);

    private:
        friend class SpriteAnimationState;

        SpriteAnimations* anims_;
    };

    class SpriteAnimationState : public ManagedItem<SpriteAnimationStates> {
    public:
        enum EndAction {
            eaStop,
            eaChangeDir,
            eaWrapAround
        };
    public:
        SpriteAnimationState();

        u32 getCurrFrameId()const;
        bool isFirstFrame()const;
        bool isLastFrame()const;
        bool isPaused()const;
        bool isForward()const;
        EndAction getEndAction()const;
        f32 getTimeToNextFrame()const;
        SpriteAnimation& getAnimation()const;
        SpriteAnimationFrame& getCurrFrame()const;
        Index getGeomId()const;

        SpriteAnimationState& flipDirection();
        SpriteAnimationState& setEndAction(EndAction ea);
        SpriteAnimationState& setPaused(bool val);
        SpriteAnimationState& setCurrFrameId(u32 f_id);
        SpriteAnimationState& setToFirstFrame();
        SpriteAnimationState& setToLastFrame();
        SpriteAnimationState& setTimeToNextFrame(f32 tnf);
        SpriteAnimationState& setForward(bool value);
        SpriteAnimationState& setGeomId(Index geom_id);
        SpriteAnimationState& setAnimationId(Index anim_id);

        // returns if frame changed (from last time)
        bool advanceAnimation(f32 dt);
    protected:

        enum Flags {
            fBackwards,
            fWrapAround,
            fPaused,
            fAutoChangeDir,
            fFrameChanged,

            flagsCount
        };

        std::bitset<flagsCount> flags_;
        u32 curr_frame_;
        f32 to_next_frame_;
        Index geom_id_;     // for connecting to geometry
        Index anim_id_;
    };

}

#include "SpriteAnimationStates.inl"
#endif //SPRITE_ANIMATION_STATES_H
