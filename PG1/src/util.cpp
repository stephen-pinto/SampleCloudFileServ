#include "../include/util.h"
#include <iostream>

using namespace std;
typedef std::ctype<wchar_t> ct_t;

//https://www.cryptopp.com/wiki/Character_Set_Considerations
//https://www.boost.org/doc/libs/1_48_0/libs/locale/doc/html/charset_handling.html

namespace cmd_line
{
    inline wstring util::widen_string(string str)
    {
        return L"";
    }

    inline string util::narrow_string(wstring str)
    {
        return "";
    }
}