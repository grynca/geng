#ifndef GEOMSTATESPRITEANIMATION_H
#define GEOMSTATESPRITEANIMATION_H

#include "GeomStateBase.h"
#include "assets.h"

namespace grynca {

    class GeomStateSpriteAnimation : public GeomStateBase {
    public:
        enum EndAction {
            eaStop,
            eaChangeDir,
            eaWrapAround
        };
    public:
        GeomStateSpriteAnimation(GeomStateType type_id, VertexData& vd, Index geom_id);

        u32 getCurrFrameId()const;
        bool isFirstFrame()const;
        bool isLastFrame()const;
        bool isPaused()const;
        bool isForward()const;
        EndAction getEndAction()const;
        f32 getTimeToNextFrame()const;
        const SpriteAnimations::IRefPtr& getAnimation()const;
        const SpriteAnimationFrame& getCurrFrame()const;

        GeomStateSpriteAnimation& flipDirection();
        GeomStateSpriteAnimation& setEndAction(EndAction ea);
        GeomStateSpriteAnimation& setPaused(bool val);
        GeomStateSpriteAnimation& setCurrFrameId(u32 f_id);
        GeomStateSpriteAnimation& setToFirstFrame();
        GeomStateSpriteAnimation& setToLastFrame();
        GeomStateSpriteAnimation& setTimeToNextFrame(f32 tnf);
        GeomStateSpriteAnimation& setForward(bool value);
        GeomStateSpriteAnimation& setAnimation(const SpriteAnimations::IRefPtr& anim);

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
        SpriteAnimations::IRefPtr animation_;
        u32 curr_frame_;
        f32 to_next_frame_;
        Index anim_id_;
    };

}

#include "GeomStateSpriteAnimation.inl"
#endif //GEOMSTATESPRITEANIMATION_H
