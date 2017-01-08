#include "TextStates.h"

namespace grynca {

    inline TextStates::TextStates(FontsPacks& fonts_packs)
     : fonts_packs_(&fonts_packs)
    {
    }

    template <typename...ConstructionArgs>
    inline TextState& TextStates::addItem(ConstructionArgs&&... args) {
        TextState& rslt = TightManager<TextState>::addItem(args...);
        rslt.setDirty(true);
        return rslt;
    }

    inline TextState::TextState()
     : font_pack_id_(Index::Invalid()), geom_id_(Index::Invalid()),  font_size_(InvalidId())
    {
        text_[0] = 0;
    }


    inline const char* TextState::getText()const {
        return text_;
    }

    inline u32 TextState::getTextSize()const {
        return strlen(text_);
    }

    inline Index TextState::getFontPackId()const {
        return font_pack_id_;
    }

    inline u32 TextState::getFontSize()const {
        return font_size_;
    }

    inline FontPack& TextState::getFontPack()const {
        return getManager().fonts_packs_->getItem(font_pack_id_);
    }

    inline Index TextState::getGeomId()const {
        return geom_id_;
    }

    inline bool TextState::isDirty()const {
        return dirty_;
    }

    inline TextState& TextState::setText(const std::string& s) {
        ASSERT(s.size()<1024);
        strcpy(text_, s.c_str());
        setDirty(true);
        return *this;
    }

    inline TextState& TextState::setFontPackId(Index fp_id) {
        font_pack_id_ = fp_id;
        setDirty(true);
        return *this;
    }

    inline TextState& TextState::setFontSize(u32 size) {
        font_size_ = size;
        setDirty(true);
        return *this;
    }

    inline TextState& TextState::setFont(const std::string& fontname, u32 size) {
        FontPack* fp = getManager().fonts_packs_->findByFontname(fontname);
        ASSERT(fp);
        font_pack_id_ = fp->getId();
        font_size_ = size;
        setDirty(true);
        return *this;
    }

    inline TextState& TextState::setGeomId(Index geom_id) {
        geom_id_ = geom_id;
        return *this;
    }

    inline TextState& TextState::setDirty(bool value) {
        if (dirty_ != value) {
            dirty_ = value;
            getManager().dirty_ids_.push_back(getId());
        }
        return *this;
    }
}