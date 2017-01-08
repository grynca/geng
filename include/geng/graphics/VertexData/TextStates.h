#ifndef TEXTSTATES_H
#define TEXTSTATES_H

#include "types/Manager.h"
#include "assets.h"

namespace grynca {

    // fw
    class TextState;

    class TextStates : public TightManager<TextState> {
    public:
        TextStates(FontsPacks& fonts_packs);

        template <typename...ConstructionArgs>
        TextState& addItem(ConstructionArgs&&... args);

        fast_vector<Index>& getDirtyIds() { return dirty_ids_; }
    private:
        friend class TextState;

        FontsPacks* fonts_packs_;
        fast_vector<Index> dirty_ids_;
    };

    class TextState : public ManagedItem<TextStates> {
    public:
        TextState();
        const char* getText()const;
        u32 getTextSize()const;
        Index getFontPackId()const;
        u32 getFontSize()const;
        FontPack& getFontPack()const;
        Index getGeomId()const;
        bool isDirty()const;

        TextState& setText(const std::string& s);
        TextState& setFontPackId(Index fp_id);
        TextState& setFontSize(u32 size);
        TextState& setFont(const std::string& fontname, u32 size);
        TextState& setGeomId(Index geom_id);
        TextState& setDirty(bool value);
    private:
        Index font_pack_id_;
        Index geom_id_;
        u32 font_size_;
        // TODO: c++11 std::string is retarded and does not work in pool (not-POD)
        //      (in windows maybe only)
        char text_[1024];
        bool dirty_;
    };

}

#include "TextStates.inl"
#endif //TEXTSTATES_H
