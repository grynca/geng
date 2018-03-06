
#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

#include "EVisual.h"

namespace grynca {

    struct CDebugOverlayData {

        static RolesMask componentRoles() { return {}; }

        enum Labels {
            lFrameInfo,
            lSecTenthInfo,
            lSecInfo,

            lCount
        };

        enum ProfileType {
            ptUpdate,
            ptRender,
            ptTick,

            ptCount
        };

        CDebugOverlayData()
         : last_sec_print(-1), last_sec_tenth_print(-1)
        {}

        struct ProfilePrintCtx {
            ProfilePrintCtx() : ready_to_update(true) {}

            bool ready_to_update;
            ustring text;
            u32 cb_id;
        };

        f32 last_sec_print;
        f32 last_sec_tenth_print;

        RefPtr<ProfilePrintCtx> ppctxs[lCount];
        EntityIndex labels[lCount];
    };

    class DebugOverlay : public EVisualT<CDebugOverlayData> {
        typedef EVisualT<CDebugOverlayData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(DebugOverlay);

        class Resources : public EntityResources<Resources> {
        public:
            void initSingleton(GameBase &game);

            FontsPacks::IRefPtr font;
            Colorf background_color;
            Colorf text_color;
            u16 layer_id;
            u32 font_size;
            f32 width, padding;
        };

        void init();
        void update();
        void onKilled();
    };

}

#include "DebugOverlay.inl"

#endif //DEBUGOVERLAY_H