#ifndef GUI_H
#define GUI_H

#include "sysent/EntityIndex.h"

namespace grynca {

    // fw
    class Window;

    class GUI {
    public:
        class InteractionCtx {
            EntityIndex mouse_over;
            EntityIndex mouse_owner;
        };

    public:
        GUI(Window& w);

        void update();

        Window& getWindow();

        bool isDebugOverlayShown()const;
        void showDebugOverlay();
        void hideDebugOverlay();
        void toggleDebugOverlay();

        bool isCollisionDebugShown()const;
        void showCollisionDebug();
        void hideCollisionDebug();
        void toggleCollisionDebug();
        EntityIndex getDebugOverlayEntityId()const;
    private:
        Window* window_;

        InteractionCtx ictx_;
        EntityIndex debug_overlay_id_;
    };

}

#include "GUI.inl"
#endif //GUI_H
