#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "../Renderable.h"
#include <bitset>

namespace grynca {

    // fw
    class Animation;
    class AssetsManager;
    class AnimationFrame;
    class TextureRegion;

    class SpriteRenderable : public Renderable
    {
    public:
        static Vec2 offsetCenter() { return Vec2{-0.5f, -0.5f}; };
        static Vec2 offsetLeftTop() { return Vec2{0,0}; }
        static Vec2 offsetRightTop() { return Vec2{-1, 0}; }
        static Vec2 offsetRightBot() { return Vec2{-1, -1}; }
        static Vec2 offsetLeftBot() { return Vec2{0, -1}; }


        enum Direction {
            dForward,
            dBackward
        };

        enum EndAction {
            eaStop,
            eaWrapAround,
            eaChangeDir
        };

        template <typename GameType>
        SpriteRenderable(GameType& game);
        template <typename GameType>
        SpriteRenderable(GameType& game, Geom& geom);       //shared geom


        SpriteRenderable& setImageRegion(const TextureRegion& tr, const Vec2& offset = offsetCenter());
        SpriteRenderable& setImageRegion(const ARect& texture_coords, const Vec2& base_size, const Vec2& offset = offsetCenter());
        SpriteRenderable& setAnimation(uint32_t animation_id);
        SpriteRenderable& setFrameId(uint32_t f_id);
        SpriteRenderable& setToFirstFrame();
        SpriteRenderable& setToLastFrame();
        SpriteRenderable& setTimeToNextFrame(float tnf);
        SpriteRenderable& setPaused(bool val);
        SpriteRenderable& setDirection(Direction dir);
        SpriteRenderable& flipDirection();
        SpriteRenderable& setEndAction(EndAction a);
        SpriteRenderable& setTextureUnit(uint32_t tid);
        SpriteRenderable& setSize(const Vec2& size);
        SpriteRenderable& setOffset(const Vec2& offset);


        bool isImage()const;
        bool isAnimation()const;
        bool isFirstFrame()const;
        bool isLastFrame()const;
        bool isPaused()const;
        AssetsManager& getAssets()const;
        Animation& getAnimation()const;
        int32_t getFrameId()const;;
        AnimationFrame& getFrame()const;;
        float getTimeToNextFrame()const;
        Direction getDirection()const;
        EndAction getEndAction()const;
        bool getFrameChanged()const;    // whether frame changed last frame
        uint32_t getTextureUnit()const;
        Vec2 getSize()const;
        Vec2 getBaseSize()const;
        Vec2 getOffset()const;
        Vec2 getBaseOffset()const;

        void advanceAnimation(float dt);    // called by system

        virtual void preRender() override;
    private:
        void setFrameInternal_(const AnimationFrame& frame);

        class AnimationState {
        public:
            enum Flags {
                fBackwards,
                fWrapAround,
                fPaused,
                fAutoChangeDir,
                fFrameChanged,

                flagsCount
            };

            AnimationState()
             : animation_id(Index::Invalid()), curr_frame(0), to_next_frame(0.0f) {}

            uint32_t animation_id;
            int32_t curr_frame;
            float to_next_frame;
            std::bitset<flagsCount> flags;
        };

        AssetsManager* assets_;
        uint32_t texture_unit_;

        AnimationState animation_state_;
    };

}

#include "SpriteRenderable.inl"
#endif //SPRITERENDERABLE_H
