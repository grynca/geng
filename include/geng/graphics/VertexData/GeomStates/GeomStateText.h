#ifndef GEOMSTATETEXT_H
#define GEOMSTATETEXT_H

#include "GeomStateBase.h"
#include "assets.h"

namespace grynca {

    class GeomStateText : public GeomStateBase {
    public:
        GeomStateText(GeomStateType type_id, VertexData& vd, Index geom_id);

        const ustring& getText()const;
        u32 getTextSize()const;
        const FontsPacks::IRefPtr& getFontPack()const;
        u32 getFontSize()const;
        f32 getLineHeight()const;
        u32 calcMaxLineSize()const;
        f32 calcHeight()const;
        f32 calcHeight(u32 lines_count)const;
        f32 calcWidth()const;
        f32 calcWidth(const ustring& line)const;  // calculates width of provided line
        f32 calcBoundWidth()const;                // calculates bound width for member text
        f32 calcBoundWidth(u32 line_size)const;

        GeomStateText& setText(const ustring& s);
        GeomStateText& setFontPack(const FontsPacks::IRefPtr& fp);
        GeomStateText& setFontSize(u32 size);
        GeomStateText& setFont(const std::string& fontname, u32 size);
        GeomStateText& setFont(const FontsPacks::IRefPtr& font_pack, u32 size);
        GeomStateText& setLineHeight(f32 lh);

        const fast_vector<u32>& getLineEnds()const;
        u32 getLinesCount()const;
        ustring getLine(u32 i)const;

        // cb(const ustring& line)
        template <typename LoopF>
        void loopLines(const LoopF& cb)const;
    private:
        static f32 calcLineHeight_(const FontPack& font_pack, u32 font_size);
        static f32 calcLineWidth_(const SizedFont& font, const ustring& line);
        FontsPacks::IRefPtr font_pack_;
        u32 font_size_;
        ustring text_;
        fast_vector<u32> line_ends_;
        f32 line_height_;
        bool auto_line_height_;
    };

}

#include "GeomStateText.inl"
#endif //GEOMSTATETEXT_H
