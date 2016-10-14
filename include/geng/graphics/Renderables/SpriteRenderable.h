#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "RenderableBase.h"
#include <bitset>

namespace grynca {

    // fw
    class Animation;
    class AssetsManager;
    class AnimationFrame;
    class TextureRegion;

    class SpriteRenderable : public RenderableBase
    {
    public:
        enum Direction {
            dForward,
            dBackward
        };

        enum EndAction {
            eaStop,
            eaWrapAround,
            eaChangeDir
        };

        SpriteRenderable();

        template <typename GameType>
        SpriteRenderable& init(GameType& game);
        template <typename GameType>
        SpriteRenderable& init(GameType& game, Geom& geom);       //reuses existing geom


        SpriteRenderable& setImageRegion(const TextureRegion& tr);
        SpriteRenderable& setImageRegion(const ARect& texture_coords, const Vec2& base_size);
        SpriteRenderable& setAnimation(Index animation_id);
        SpriteRenderable& setFrameId(uint32_t f_id);
        SpriteRenderable& setToFirstFrame();
        SpriteRenderable& setToLastFrame();
        SpriteRenderable& setTimeToNextFrame(float tnf);
        SpriteRenderable& setPaused(bool val);
        SpriteRenderable& setDirection(Direction dir);
        SpriteRenderable& flipDirection();
        SpriteRenderable& setEndAction(EndAction a);
        SpriteRenderable& setTextureUnit(uint32_t tid);
        SpriteRenderable& setSize(const Vec2& size);        // sets local transform's scale
        SpriteRenderable& setNormOffset(const Vec2& offset);


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
        Vec2 getGeomSize()const;
        Vec2 getNormOffset()const;
        Vec2 getGeomOffset()const;      // in pixels in base image size scale

        void advanceAnimation(float dt);    // called by system

        virtual void setUniforms(const Mat3& mvp, Shader& s) override;
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

            Index animation_id;
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
