#include "GUI.h"

namespace grynca {

    inline GUI::GUI(Window& w)
     : window_(&w)
    {
    }

    void GUI::update() {

    }

    inline Window& GUI::getWindow() {
        return *window_;
    }
}