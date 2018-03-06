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

        virtual ~Game();

        const Window& getWindow()const;
        Window& accWindow();

        Game& asGame();
        const Game& asGame()const;
    protected:
        Game(const std::string& name = "Grynca Game", u32 width = 1024, u32 height = 768);
        Game(const Game&) {}
    private:
        virtual void initEMInner_(u32 initial_ents_reserve) override;
        virtual void initInner_() override;
        virtual void updateInner_() override;
        virtual void tickInner_() override;
        virtual void renderInner_(f32 dt) override;
    };

}
#endif //GAME_H

#if !defined(GAME_INL) && !defined(WITHOUT_IMPL)
#   define GAME_INL
#   include "Game.inl"
#endif // GAME_INL
