#include "VertexDataPT.h"
#include "../Window.h"
#include "Factories/geom_factories.h"
#include "geng/graphics/VertexData/GeomStates/GeomStateSpriteAnimation.h"
#include "geng/graphics/VertexData/GeomStates/GeomStateText.h"
#include "../../Game.h"

namespace grynca {

    inline void VertexDataPT::initSingleton() {
        setVertexLayout<Vertex>({{ Shader::getVertexAttribId("v_pos_uv"), 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos)}});
        accGeomStates().initStateType<GeomStateText>(gstText);
        accGeomStates().initStateType<GeomStateSpriteAnimation>(gstAnimationSprite);
        initSharedQuadGeomPositions<Vertex>();
    }

    inline void VertexDataPT::update(f32 dt) {
        // update texts
        for (u32 i=0; i<getGeomStates().getDirtyStatesCount(gstText); ++i) {
            GeomStateText& ts = *(GeomStateText*)(accGeomStates().getDirtyState(gstText, i));
            Geom& geom = ts.accGeom();

            geom.removeAllVertices();
            const FontPack& fp = ts.getFontPack().get();
            const SizedFont& font = fp.getFont().getSizedFont(ts.getFontSize());
            FactoryRectT<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectT<VertexDataPT::Vertex> >();
            const fast_vector<u32>& line_ends = ts.getLineEnds();
            f32 ypos = 0;
            u32 char_id = 0;
            for (u32 j=0; j<line_ends.size(); ++j) {
                f32 xpos = 0;
                for (; char_id<line_ends[j]; ++char_id) {
                    const Glyph& g = font.getGlyph(ts.getText()[char_id]);
                    const TextureRegion& tex_r = g.getRegion();

                    Vec2 offset(xpos+g.getOffsetX(), ypos + ts.getLineHeight() - g.getOffsetY());
                    u32 start_vert = fact.add(tex_r.getRect().getSize(), offset);
                    fact.setTC(start_vert, tex_r.getTextureRect().getLeftTop(), tex_r.getTextureRect().getRightBot());
                    xpos += g.getAdvanceX();
                }
                ypos += ts.getLineHeight();
                ++char_id;
            }
            ts.clearDirty();
        }
        accGeomStates().clearDirtyStates(gstText);


        // update animation states
        for (u32 i=0; i<getGeomStates().getStatesCount(gstAnimationSprite); ++i) {
            GeomStateSpriteAnimation& sas = *(GeomStateSpriteAnimation*)(accGeomStates().accState(gstAnimationSprite, i));
            if (sas.advanceAnimation(dt)) {
                // update geoms with new animation frames
                Geom& geom = sas.accGeom();
                const SpriteAnimationFrame& f = sas.getCurrFrame();

                const ARect& tr = f.getRegion().getTextureRect();
                FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<Vertex> >();
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

}