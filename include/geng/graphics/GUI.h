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
    private:
        Window* window_;

        InteractionCtx ictx_;
    };

}

#include "GUI.inl"
#endif //GUI_H
