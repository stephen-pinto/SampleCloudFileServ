#include "../include/cmd_line_provider.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace cmd_tool;
using namespace std;
using namespace boost;
string binary_commands[] = {"rm", "cp"};

int cmd_line_provider::run(int argc, char** argv)
{
    string input;

    while(true)
    {
        cout << "$> ";
        getline(cin, input);

        //If exit invoked the break out
        if(input == "exit")
            break;
        
        //Handle the command
        int res = handle_command(input);

        cout << endl;

        //Incase a command failed then return appropriate status
        if(res != 0)
            return res;        
    }

    return 0;
}

int cmd_line_provider::handle_command(string command)
{
    vector<string> command_parms;

    split(command_parms, command, is_any_of(" "));
    
    //If its a binary command then let the other function handle it
    if(command_parms.size() > 1)
        return handle_binary_command(command_parms);

    //For all other types of commands handle here
    if (command == "ls")
    {
        cout << "first" << endl;
        cout << "second" << endl;
    }
    else if(command == "pwd")
    {
        cout << "c:/unit/cpp" << endl;
    }
    else 
    {
        //If the command was a binary command but without args
        for(auto item : binary_commands)
        {
            if(starts_with(command, item))
            {
                cout << "Not enough arguments passed to command" << endl;
                return 0;
            }
        }

        //In all other cases
        cout << "Specified command not supported" << endl;
    }

    return 0;
}

int cmd_line_provider::handle_binary_command(std::vector<std::string> params)
{
    if(params.front() == "rm")
    {
        cout << "Removed file " << params.back() << endl;
    }

    return 0;
}