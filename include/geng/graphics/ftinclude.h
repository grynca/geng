#ifndef FTINCLUDE_H
#define FTINCLUDE_H

#include "types/Exception.h"
#include <sstream>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//#undef __FTERRORS_H__
//#define FT_ERRORDEF( e, v, s )  { e, s },
//#define FT_ERROR_START_LIST     {
//#define FT_ERROR_END_LIST       { 0, 0 } };
//const struct {
//    int          code;
//    const char*  message;
//} FT_Errors[] =
//#include FT_ERRORS_H

namespace geng {

//    struct FT_Exception : public Exception
//    {
//        FT_Exception(int error) throw()
//         : Exception(std::string("FreeType: ") + getFTErrorMsg_(error)) {}
//
//        FT_Exception(const char * text, int error) throw()
//         : Exception(std::string("FreeType: ") + text + "-" + getFTErrorMsg_(error)) {}
//    private:
//        std::string FT_Exception::getFTErrorMsg_(int error) {
//        // static
//            std::stringstream ss;
//            ss << FT_Errors[error].code << ", " << FT_Errors[error].message;
//            return ss.str();
//        }
//    };

}


#endif //FTINCLUDE_H
