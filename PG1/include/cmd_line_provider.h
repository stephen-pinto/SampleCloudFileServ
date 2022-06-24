#ifndef __CMD_LINE_PROVIDER_H__
#define __CMD_LINE_PROVIDER_H__

#include <string>

namespace cmd_tool
{
    class cmd_line_provider
    {
    public:
        int run(int argc, char** argv);
    private:
        int handle_command(const std::string command);
    };
}

#endif // __CMD_LINE_PROVIDER_H__