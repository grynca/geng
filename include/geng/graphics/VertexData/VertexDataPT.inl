#include "VertexDataPT.h"
#include "../Window.h"
#include "Factories/geom_factories.h"
#include "SpriteAnimationStates.h"
#include "TextStates.h"
#include "../../Game.h"

namespace grynca {

    inline VertexDataPT::VertexDataPT()
     : text_states_(NULL), anim_states_(NULL)
    {
        setVertexLayout<Vertex>({{ Shader::getVertexAttribId("v_pos_uv"), 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos)}});
    }

    inline void VertexDataPT::init() {
        AssetsManager& assets = getManager().getWindow().getGame().getModule<AssetsManager>();
        anim_states_ = new SpriteAnimationStates(assets.getSpriteAnimations());
        text_states_ = new TextStates(assets.getFontsPacks());
    }

    inline VertexDataPT::~VertexDataPT() {
        if (anim_states_)
            delete anim_states_;
        if (text_states_)
            delete text_states_;
    }

    inline TextStates& VertexDataPT::getTextStates() {
        return *text_states_;
    }

    inline SpriteAnimationStates& VertexDataPT::getSpriteAnimationsStates() {
        return *anim_states_;
    }

    inline void VertexDataPT::update(f32 dt) {
        // update texts
        for (u32 i=0; i<text_states_->getDirtyIds().size(); ++i) {
            Index dirty_id = text_states_->getDirtyIds()[i];
            TextState& ts = text_states_->getItem(dirty_id);
            Geom& g = this->getItem(ts.getGeomId());

            g.removeAllVertices();
            FontPack& fp = ts.getFontPack();
            const SizedFont& font = fp.getFont().getSizedFont(ts.getFontSize());
            f32 xpos = 0;
            FactoryRectT<VertexDataPT::Vertex> fact = g.getFactory<FactoryRectT<VertexDataPT::Vertex> >();
            for (u32 i=0; i<ts.getTextSize(); ++i) {
                const Glyph& g = font.getGlyph(ts.getText()[i]);
                const TextureRegion& tex_r = g.getRegion();

                Vec2 offset(xpos+g.getOffsetX(), -g.getOffsetY());
                u32 start_vert = fact.add(tex_r.getRect().getSize(), offset);
                fact.setTC(start_vert, tex_r.getTextureRect().getLeftTop(), tex_r.getTextureRect().getRightBot());
                xpos += g.getAdvanceX();
            }
            ts.setDirty(false);
        }
        text_states_->getDirtyIds().clear();


        // update animation states
        for (u32 i=0; i<anim_states_->getItemsCount(); ++i) {
            SpriteAnimationState& s = anim_states_->getItemAtPos2(i);
            if (s.advanceAnimation(dt)) {
                // update geoms with new animation frames
                Geom& g = this->getItem(s.getGeomId());
                SpriteAnimationFrame& f = s.getCurrFrame();

                const ARect& tr = f.getRegion().getTextureRect();
                FactoryRectTF<VertexDataPT::Vertex> fact = g.getFactory<FactoryRectTF<Vertex> >();
                Vec2 prev_base_size = fact.getSize(0);
                Vec2 offset = fact.getOffset(0)/prev_base_size;
                Vec2 new_base_size = f.getRegion().getRect().getSize();
                fact.setSize(0, new_base_size);
                fact.setOffset(0, new_base_size*offset);
                fact.setTC(0, tr.getLeftTop(), tr.getRightBot());
            }
        }

        // update vertices
        VertexData::update(dt);
    }

    inline Index VertexDataPT::beforeGeomChangedState_(Geom& g, GeomState::StateType old_type, GeomState::StateType new_type) {
        Index new_state_id = Index::Invalid();
        switch (old_type) {
            case GeomState::stAnimation:
                anim_states_->removeItem(g.getGeomStateId());
                break;
            case GeomState::stText:
                text_states_->removeItem(g.getGeomStateId());
                break;
            case GeomState::stNone:
            default:
                break;
        }

        switch (new_type) {
            case GeomState::stAnimation: {
                SpriteAnimationState& s = anim_states_->addItem();
                s.setGeomId(g.getId());
                new_state_id = s.getId();
            }break;
            case GeomState::stText: {
                TextState& s = text_states_->addItem();
                s.setGeomId(g.getId());
                new_state_id = s.getId();
            }break;
            case GeomState::stNone:
            default:
                break;
        }
        return new_state_id;
    }

}