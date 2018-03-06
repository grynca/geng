#include "GeomStateText.h"
#include "GeomStateBase.h"

namespace grynca {

    inline GeomStateText::GeomStateText(GeomStateType type_id, VertexData& vd, Index geom_id)
     : GeomStateBase(type_id, vd, geom_id),
       font_size_(InvalidId()), line_height_(-1.0f), auto_line_height_(true)
    {
    }

    inline const ustring& GeomStateText::getText()const {
        return text_;
    }

    inline u32 GeomStateText::getTextSize()const {
        return u32(text_.length());
    }

    inline const FontsPacks::IRefPtr& GeomStateText::getFontPack()const {
        return font_pack_;
    }

    inline u32 GeomStateText::getFontSize()const {
        return font_size_;
    }

    inline u32 GeomStateText::calcMaxLineSize()const {
        u32 max_line_size = line_ends_[0];
        for (u32 i=1; i<line_ends_.size(); ++i) {
            u32 line_size = line_ends_[i] - line_ends_[i-1];
            if (line_size > max_line_size) {
                max_line_size = line_size;
            }
        }
        return max_line_size;
    }

    inline f32 GeomStateText::getLineHeight()const {
        return line_height_;
    }

    inline f32 GeomStateText::calcHeight()const {
        return calcHeight(getLinesCount());
    }

    inline f32 GeomStateText::calcHeight(u32 lines_count)const {
        return lines_count * getLineHeight();
    }

    inline f32 GeomStateText::calcWidth()const {
        const SizedFont& font = font_pack_.get().getFont().getSizedFont(font_size_);
        f32 max_width = 0.0f;
        loopLines([this, &font, &max_width](const ustring& line) {
            f32 width = calcLineWidth_(font, line);
            if (width > max_width) {
                max_width = width;
            }
        });
        return max_width;
    }

    inline f32 GeomStateText::calcWidth(const ustring& line)const {
        const SizedFont& font = font_pack_.get().getFont().getSizedFont(font_size_);
        return calcLineWidth_(font, line);
    }

    inline f32 GeomStateText::calcBoundWidth()const {
        u32 max_line_size = calcMaxLineSize();
        return calcBoundWidth(max_line_size);
    }

    inline f32 GeomStateText::calcBoundWidth(u32 line_size)const {
        const SizedFont& font = font_pack_.get().getFont().getSizedFont(font_size_);
        return font.getGlyph('M').getAdvanceX()*line_size;
    }

    inline GeomStateText& GeomStateText::setText(const ustring& s) {
        text_ = s;
        line_ends_.clear();
        for (u32 i=0; i<s.size(); ++i) {
            if (s[i] == '\n') {
                line_ends_.push_back(i);
            }
        }
        line_ends_.push_back(u32(s.size()));
        makeDirty();
        return *this;
    }

    inline GeomStateText& GeomStateText::setFontPack(const FontsPacks::IRefPtr& fp) {
        font_pack_ = fp;
        makeDirty();
        if (auto_line_height_ && font_size_ != InvalidId()) {
            line_height_ = calcLineHeight_(font_pack_.get(), font_size_);
        }
        return *this;
    }

    inline GeomStateText& GeomStateText::setFontSize(u32 size) {
        font_size_ = size;
        if (auto_line_height_ && !font_pack_.isNull()) {
            line_height_ = calcLineHeight_(font_pack_.get(), font_size_);
        }
        makeDirty();
        return *this;
    }

    inline GeomStateText& GeomStateText::setFont(const std::string& fontname, u32 size) {
        FontPack* fp = font_pack_->getManager().findByFontname(fontname);
        ASSERT(fp);
        font_pack_ = *fp;
        font_size_ = size;
        if (auto_line_height_) {
            line_height_ = calcLineHeight_(*fp, font_size_);
        }
        makeDirty();
        return *this;
    }

    inline GeomStateText& GeomStateText::setFont(const FontsPacks::IRefPtr& font_pack, u32 size) {
        font_pack_ = font_pack;
        font_size_ = size;
        if (auto_line_height_) {
            line_height_ = calcLineHeight_(font_pack_.get(), font_size_);
        }
        makeDirty();
        return *this;
    }

    inline GeomStateText& GeomStateText::setLineHeight(f32 lh) {
        auto_line_height_ = false;
        line_height_ = lh;
        return *this;
    }

    inline u32 GeomStateText::getLinesCount()const {
        return u32(line_ends_.size());
    }

    inline const fast_vector<u32>& GeomStateText::getLineEnds()const {
        return line_ends_;
    }

    inline ustring GeomStateText::getLine(u32 i)const {
        u32 from = (i>0)?line_ends_[i-1]:0;
        u32 to = line_ends_[i];
        return text_.substr(from, to-from);
    }

    template <typename LoopF>
    inline void GeomStateText::loopLines(const LoopF& cb)const {
        // first line
        u32 prev_end = line_ends_[0];
        cb(text_.substr(0, prev_end));
        for (u32 i=1; i<getLinesCount(); ++i) {
            cb(text_.substr(prev_end, line_ends_[i]-prev_end));
            prev_end = line_ends_[i];
        }
    }

    inline f32 GeomStateText::calcLineHeight_(const FontPack& font_pack, u32 font_size) {
        // static
        const SizedFont& font = font_pack.getFont().getSizedFont(font_size);
        return font.getGlyph('M').getOffsetY() *1.5f;
    }

    inline f32 GeomStateText::calcLineWidth_(const SizedFont& font, const ustring& line) {
        // static
        f32 rslt = 0.0f;
        for (u32 i=0; i<line.length(); ++i) {
            rslt += font.getGlyph(line[i]).getAdvanceX();
        }
        return rslt;
    }
}