#ifndef FRAME_H
#define FRAME_H

namespace grynca {

    enum CoordFrame {
        // 0,0 is left-top of screen, coords are pixels
        cfScreenLocal,
        cfScreenGlobal,

        cfWorldLocal,
        cfWorldGlobal
    };
}

#endif //FRAME_H
