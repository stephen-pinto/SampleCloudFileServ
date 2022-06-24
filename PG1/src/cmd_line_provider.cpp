#include "../include/cmd_line_provider.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace cmd_tool;
using namespace std;
using namespace boost;

int cmd_line_provider::run(int argc, char** argv)
{
    string input;

    while(true)
    {
        cout << "$> ";
        cin >> input;

        //If exit invoked the break out
        if(input == "exit()")
            break;
        
        //Handle the command
        int res = handle_command(input);

        //Incase a command failed then return appropriate status
        if(res != 0)
            return res;        
    }

    return 0;
}

int cmd_line_provider::handle_command(string command)
{
    if(command == "ls")
    {
        cout << "first" << endl;
        cout << "second" << endl;
    }
    else if(command == "pwd")
    {
        cout << "c:/unit/cpp" << endl;
    }
    else if(starts_with(command, "rm"))
    {
        cout << "specified file removed" << endl;
    }
    else 
    {
        cout << "Specified command not supported" << endl;
    }

    return 0;
}