#ifndef __CMD_LINE_PROVIDER_H__
#define __CMD_LINE_PROVIDER_H__

#include <string>
#include <vector>
#include "../include/common.h"

namespace cmd_tool
{
    class cmd_line_provider
    {
    public:
        int run(int argc, char** argv);
    private:
        int handle_command(const std::string command);
        int handle_binary_command(std::vector<std::string> params);
    };
}

#endif // __CMD_LINE_PROVIDER_H__