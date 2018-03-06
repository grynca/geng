#include "GUI.h"
#include "Components/CRenderable.h"
#include "Entities/DebugOverlay.h"
#include "../physics/Systems/BoundsDebugRenderSystem.h"
#include "Systems/RenderSystem.h"

namespace grynca {

    inline GUI::GUI(Window& w)
     : window_(&w), debug_overlay_id_(EntityIndex::Invalid())
    {
    }

    void GUI::update() {
        if (isDebugOverlayShown()) {
            window_->getGame().getEntitiesManager().getEntity<DebugOverlay>(debug_overlay_id_).update();
        }
    }

    inline Window& GUI::getWindow() {
        return *window_;
    }

    inline bool GUI::isDebugOverlayShown()const {
        return debug_overlay_id_.isValid();
    }

    inline void GUI::showDebugOverlay() {
        ASSERT(!isDebugOverlayShown());
        Game& g = window_->getGame();
        debug_overlay_id_ = g.createAndInitEntity<DebugOverlay>().getEntity().getIndex();
    }

    inline void GUI::hideDebugOverlay() {
        ASSERT(isDebugOverlayShown());
        Game& g = window_->getGame();
        g.getEntitiesManager().getEntity(debug_overlay_id_).kill();
        debug_overlay_id_ = EntityIndex::Invalid();
    }

    inline void GUI::toggleDebugOverlay() {
        if (isDebugOverlayShown())
            hideDebugOverlay();
        else
            showDebugOverlay();
    }

    inline bool GUI::isCollisionDebugShown()const {
        BoundsDebugRenderSystem* cds = window_->getGame().getRenderSystem<BoundsDebugRenderSystem>();
        return cds && cds->isEnabled();
    }

    inline void GUI::showCollisionDebug() {
        ASSERT(!isCollisionDebugShown());
        Game& g = window_->getGame();
        BoundsDebugRenderSystem* cds = g.getRenderSystem<BoundsDebugRenderSystem>();
        if (cds && !cds->isEnabled()) {
            g.getRenderSystem<BoundsDebugRenderSystem>()->enable();
        }
    }

    inline void GUI::hideCollisionDebug() {
        ASSERT(isCollisionDebugShown());
        Game& g = window_->getGame();
        BoundsDebugRenderSystem* cds = g.getRenderSystem<BoundsDebugRenderSystem>();
        if (cds && cds->isEnabled()) {
            g.getRenderSystem<BoundsDebugRenderSystem>()->disable();
        }
    }

    inline void GUI::toggleCollisionDebug() {
        if (isCollisionDebugShown())
            hideCollisionDebug();
        else
            showCollisionDebug();
    }

    inline EntityIndex GUI::getDebugOverlayEntityId()const {
        return debug_overlay_id_;
    }
}