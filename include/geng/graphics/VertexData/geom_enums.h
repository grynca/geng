#ifndef GEOMENUMS_H
#define GEOMENUMS_H

enum GeomUsageHint {
    uhStatic,       // set once use a lot
    uhDynamic,      // set a lot use a lot
    uhStream,        // set once use once


    uhCount
};

enum GeomStateType {
    gstNone,
    gstText,
    gstAnimationSprite,
    gstParticles,

    gstCount
};

#endif //GEOMENUMS_H
