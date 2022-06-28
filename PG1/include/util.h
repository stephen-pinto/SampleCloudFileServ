#ifndef __UTIL_H__
#define __UTIL_H__
#include <string>

namespace cmd_line
{
    class  util
    {        
    public:
        inline std::wstring widen_string(std::string str);
        inline std::string narrow_string(std::wstring str);

    private:
    };
} // namespace cmd_line

#endif // __UTIL_H__