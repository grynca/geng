#include "Game.h"
#include "graphics/graphics_includes.h"

namespace grynca {

    inline Game::Game(const std::string& name, u32 width, u32 height) {
        Window& window = initModule<Window>();

        window.init(*this, name, width, height);
        window.getShaders().initSingletons<ShaderTypes>();
        window.getVertices().initSingletons<VertexDataTypes>();
        window.getRenderer().initRenderableTypes<RenderableTypes>();

        SIMPLE_FUNCTOR(QuitHandler, (Game* me, SDL_Event& e) {
            me->quit();
            return false;
        });
        window.getEvents().addCallback(SDL_QUIT, Events::CbFunc::create<QuitHandler>(this));
    }

    void Game::initEMInner_(u32 initial_ents_reserve) {
        GameBase::initEMInner_(initial_ents_reserve);
#ifdef PROFILE_BUILD
        addEMTypes_<TypesPack<DebugOverlay>>(1);
#endif
        addEMTypes_<GraphicsEntityTypes>(initial_ents_reserve);
    }

    inline void Game::initInner_() {
#ifdef DEBUG_BUILD
        std::cout << getWindow().getShaders().getTypesDebugString() << std::endl;
        std::cout << getWindow().getVertices().getTypesDebugString() << std::endl;
#endif
        GameBase::initInner_();
#ifdef PROFILE_BUILD
        getWindow().getGUI().showDebugOverlay();
        std::cout << "press Alt+O to toggle Debug overlay" << std::endl;
        std::cout << "press Alt+P to toggle Collision Debug" << std::endl;
#endif
    }

    inline void Game::updateInner_() {
        Window &window = accWindow();

#ifdef PROFILE_BUILD
        Events& events = window.getEvents();
        bool altDown = events.isKeyDown(SDL_SCANCODE_LALT) || events.isKeyDown(SDL_SCANCODE_RALT);
        if (altDown && events.wasKeyPressed(SDL_SCANCODE_O)) {
            window.getGUI().toggleDebugOverlay();
        }
        if (altDown && events.wasKeyPressed(SDL_SCANCODE_P)) {
            window.getGUI().toggleCollisionDebug();
        }
#endif
        window.getEvents().update();
        GameBase::updateInner_();
    }

    inline void Game::tickInner_() {
        GameBase::tickInner_();
    }

    inline void Game::renderInner_(f32 dt) {
        Window& window = accWindow();
        window.clear();
        window.accViewPort().updateMatrices();
        GameBase::renderInner_(dt);
    }

    inline Game::~Game() {
        // must destroy systems first (because they can have references to some managed objects (Geoms ...))
        accEntitiesManager().destroy();
    }

    inline const Window& Game::getWindow()const {
        return this->template getModule<Window>();
    }

    inline Window& Game::accWindow() {
        return this->template accModule<Window>();
    }

    inline Game& Game::asGame() {
        return *this;
    }

    inline const Game& Game::asGame()const {
        return *this;
    }
}