#include "DebugOverlay.h"
#include "EVisual.h"
#include "../Renderables/TextRenderable.h"
#include "../Renderables/RectRenderable.h"
#include "../VertexData/VertexDataParticles.h"
#include "../graphics_config.h"

namespace grynca {

    inline void DebugOverlay::Resources::initSingleton(GameBase &game) {
        FontsPacks& fonts = game.getModule<Window>().getAssets().getFontsPacks();
        font = fonts.findByFontname("courier");
        if (!font.isValid()) {
            // just getTransform first font
            ASSERT_M(fonts.getItemsCount(), "No fonts loaded, cant create debug overlay");
            font =  fonts.accItemAtPos(0);
        }
        layer_id = config::MAX_LAYERS-2;
        background_color = Colorf::White();
        background_color.a = 0.78f;
        text_color = Colorf::Black();
        text_color.a = 0.5f;
        font_size = 13;
        width = 600;
        padding = 10;
    }


    inline void DebugOverlay::init() {
        static Resources &res = Resources::get();
        static Game& game = Game::get();

        Vec2 screen_size = game.getWindow().getViewPort().getBaseSize();
        Vec2 pos(screen_size.getX() - res.width - res.padding, res.padding);

        DebugOverlay& background = *this;
        {
            CTransformSetter trs = background.get<CTransformSetter>();
            CRenderable rend = background.get<CRenderable>();

            RectRenderable* bckg_r = rend.initR<RectRenderable>();
            bckg_r->setStaticSharedQuadGeom(NormOffset::otLeftTop);
            bckg_r->setSize({res.width, screen_size.getY()-res.padding*2});
            bckg_r->setColor(res.background_color);
            bckg_r->setLayer(res.layer_id);
            rend.setScreenFrame(true);

            trs.move(pos);
        }

        CDebugOverlayData* cdo = background.getData<CDebugOverlayData>();

        // init labels
        for (u32 i=0; i<CDebugOverlayData::lCount; ++i) {
            EVisual lbl = game.createEntity<EVisual>();
            CRenderable rend = lbl.get<CRenderable>();

            TextRenderable* lbl_r = rend.initR<TextRenderable>();
            lbl_r->setNewGeom();
            lbl_r->setColor(res.text_color);
            lbl_r->accTextState().setFont(res.font, res.font_size);
            lbl_r->setLayer(res.layer_id+1);
            rend.setScreenFrame(true);

            cdo->labels[i] = lbl.getEntityIndex();
        }

        // set first label position directly, others will be set in update dynamically
        pos += {res.padding, res.padding};
        game.getEntity(cdo->labels[CDebugOverlayData::lFrameInfo]).get<CTransformSetter>().move(pos);

        // Hook profiling callbacks on game's profiling callbacks
        SIMPLE_FUNCTOR(ProfilePrinterRenderUpdate, (CDebugOverlayData::ProfilePrintCtx* ppctx, const ProfilingSample& s) {
                // state controls when profiling text gets updated in order to not update too frequently
                if (ppctx->ready_to_update) {
                    ppctx->text = s.simplePrint(1.0f);
                    ppctx->ready_to_update = false;
                }
        });

        cdo->ppctxs[GameBase::ptRender] = new CDebugOverlayData::ProfilePrintCtx();
        auto cbr = createEventCbWithObjRC<ProfilePrinterRenderUpdate, CDebugOverlayData::ProfilePrintCtx>(cdo->ppctxs[GameBase::ptRender]);
        cdo->ppctxs[GameBase::ptRender]->cb_id = game.accProfilingCallbacks(GameBase::ptRender).addLast(cbr).getId().callback_id;

        cdo->ppctxs[GameBase::ptUpdate] = new CDebugOverlayData::ProfilePrintCtx();
        auto cbu = createEventCbWithObjRC<ProfilePrinterRenderUpdate, CDebugOverlayData::ProfilePrintCtx>(cdo->ppctxs[GameBase::ptUpdate]);
        cdo->ppctxs[GameBase::ptUpdate]->cb_id = game.accProfilingCallbacks(GameBase::ptUpdate).addLast(cbu).getId().callback_id;

        SIMPLE_FUNCTOR(ProfilePrinterTick, (CDebugOverlayData::ProfilePrintCtx* ppctx, const ProfilingSample& s) {
                // Tick profiling text gets updated every time (once per second)
                ppctx->text = s.simplePrint(1.0f);
        });

        cdo->ppctxs[GameBase::ptTick] = new CDebugOverlayData::ProfilePrintCtx();
        auto cbt = createEventCbWithObjRC<ProfilePrinterRenderUpdate, CDebugOverlayData::ProfilePrintCtx>(cdo->ppctxs[GameBase::ptTick]);
        cdo->ppctxs[GameBase::ptTick]->cb_id = game.accProfilingCallbacks(GameBase::ptTick).addLast(cbt).getId().callback_id;
    }

    inline void DebugOverlay::update() {
        static Game& game = Game::get();

        const Window& w = game.getWindow();
        CDebugOverlayData* cdo = getData<CDebugOverlayData>();

        Vec2 pos;
        // info changed each frame
        {
            EVisual lbl = game.getEntity<EVisual>(cdo->labels[CDebugOverlayData::lFrameInfo]);
            CRenderable rend = lbl.get<CRenderable>();
            CTransformData* trd = lbl.getData<CTransformData>();

            f32 frame_time = FPR(1000.0f/game.getFPS(), 3);
            u32 particles_cnt = w.getVertices().getFast<VertexDataParticles>().getParticlesCount();
            std::stringstream ss;
            ss << "FPS: " << game.getFPS() << " (" << frame_time << "ms)" << std::endl
               << "UPS: " << game.getUPS() << std::endl
               << "Lag: " << game.getLag() << std::endl
               << "Entities: " << game.getEntitiesManager().getEntitiesCount() << std::endl
               << "Particles: " << particles_cnt << std::endl;

            TextRenderable* lbl_r = rend.accR<TextRenderable>();
            lbl_r->accTextState().setText(ss.str());
            pos = trd->getPosition() + Vec2(0, lbl_r->getTextState().calcHeight() + 5);
        }

        // info changed each 1/10 th of second
        {
            EVisual lbl = game.getEntity<EVisual>(cdo->labels[CDebugOverlayData::lSecTenthInfo]);
            CRenderable rend = lbl.get<CRenderable>();
            CTransformSetter trs = lbl.get<CTransformSetter>();

            TextRenderable* lbl_r = rend.accR<TextRenderable>();

            f32 sec_tenth = u32(game.getTimer().getElapsed()*10);
            if (sec_tenth != cdo->last_sec_tenth_print) {
                std::stringstream ss;
                for (u32 i=0; i<GameBase::ptCount; ++i) {
                    ss << cdo->ppctxs[i]->text << std::endl;
                    cdo->ppctxs[i]->ready_to_update = true;
                }

                lbl_r->accTextState().setText(ss.str());
                cdo->last_sec_tenth_print = sec_tenth;
            }
            trs.setPosition(pos);
            pos.accY() += lbl_r->getTextState().calcHeight() + 5;
        }

        // info changes each second
        {
            EVisual lbl = game.getEntity<EVisual>(cdo->labels[CDebugOverlayData::lSecInfo]);
            CRenderable rend = lbl.get<CRenderable>();
            CTransformSetter trs = lbl.get<CTransformSetter>();

            f32 sec = u32(game.getTimer().getElapsed());
            if (sec != cdo->last_sec_print) {
                TextRenderable* lbl_r = rend.accR<TextRenderable>();
                std::string log = w.getVertices().getDebugString(0);
//#ifdef PROFILE_BUILD
//              log += "\n" + game.getEntitiesManager().getProfileString();
//#endif
                lbl_r->accTextState().setText(log);
                cdo->last_sec_print = sec;
            }
            trs.setPosition(pos);
        }
    }

    inline void DebugOverlay::onKilled() {
        static Game& game = Game::get();

        CDebugOverlayData* cdo = getData<CDebugOverlayData>();
        // kill labels
        for (u32 i=0; i<CDebugOverlayData::lCount; ++i) {
            game.getEntity(cdo->labels[i]).kill();
        }

        for (u32 i=0; i<GameBase::ptCount; ++i) {
            game.accProfilingCallbacks(i).removeItem(cdo->ppctxs[i]->cb_id);
        }
    }
}