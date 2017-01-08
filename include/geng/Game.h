#ifndef GAME_H
#define GAME_H

#include "GameBase.h"

namespace grynca {

    class Window;

    class Game : public GameBase
    {
    public:
        static Game& get() {
            return (Game&)GameBase::get();
        }

        Window& getWindow();
    protected:
        Game(const std::string& name = "Grynca Game", u32 width = 1024, u32 height = 768);
        Game(const Game&) {}
    private:

        virtual void updateInner_() override;
        virtual void tickInner_() override;
        virtual void renderInner_(f32 dt) override;
    };

}

#include "Game.inl"
#endif //GAME_H
