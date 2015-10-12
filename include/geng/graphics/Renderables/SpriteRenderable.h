#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "../Renderable.h"
#include <bitset>

namespace grynca {

    // fw
    class Animation;
    class AssetsManager;

    class SpriteRenderable : public Renderable
    {
    public:
        SpriteRenderable();

        template <typename GameType>
        SpriteRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id);
        template <typename GameType>
        SpriteRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id, const Vec2& size);
        template <typename GameType>
        SpriteRenderable& init(GameType& game, uint32_t layer_id, uint32_t texture_unit, uint32_t animation_id, const Vec2& size, const Vec2& offset);

        void setAnimationId(uint32_t animation_id);
        int32_t getFrameId()const;
        bool isFirstFrame()const;
        bool isLastFrame()const;
        void setToFirstFrame();
        void setToLastFrame() ;
        Animation& getAnimation();
        float getToNextFrame()const;
        void setFrameId(uint32_t f_id);
        void setToNextFrame(float tnf);
        void changeDirection();
        bool isGoingBackward()const;
        bool isGoingForward()const;
        bool getWrapAround()const;
        void setWrapAround(bool val);
        bool isPaused()const;
        void setPaused(bool val);
        bool getAutoChangeDir()const;
        void setAutoChangeDir(bool val);
        bool getFrameChanged()const;
        AssetsManager& getAssets();
        void advanceAnimation(float dt);

        uint32_t getTextureUnit()const;
        void setTextureUnit(uint32_t tid);
        Vec2 getSize();
        Vec2 getOffset();
        void setSize(const Vec2& size);
        void setOffset(const Vec2& offset);

        virtual void preRender() override;

    private:
        AssetsManager* assets_;
        uint32_t texture_unit_;
        uint32_t animation_id_;
        int32_t curr_frame_;
        float to_next_frame_;
        std::bitset<5> flags_;
    };

}

#include "SpriteRenderable.inl"
#endif //SPRITERENDERABLE_H
