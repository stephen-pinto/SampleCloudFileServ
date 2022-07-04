#include "pch.h"
#include "..\include\CommandLineProvider.h"
#include <boost/algorithm/string.hpp>

using namespace CloudFileServLib::BL;
using namespace std;
using namespace boost;

string binaryCmds[] = { "rm", "cp" };

int Run(int argc, char** argv)
{
    string input;

    while (true)
    {
        cout << "$> ";
        getline(cin, input);

        //If exit invoked the break out
        if (input == "exit")
            break;

        //Handle the command
        int res = HandleCommand(input);

        cout << endl;

        //Incase a command failed then return appropriate status
        if (res != 0)
            return res;
    }

    return 0;
}

int HandleCommand(string command)
{
    vector<string> cmdParams;

    split(cmdParams, command, is_any_of(" "));

    //If its a binary command then let the other function handle it
    if (cmdParams.size() > 1)
        return HandleBinaryCommand(cmdParams);

    //For all other types of commands handle here
    if (command == "ls")
    {
        cout << "first" << endl;
        cout << "second" << endl;
    }
    else if (command == "pwd")
    {
        cout << "c:/unit/cpp" << endl;
    }
    else
    {
        //If the command was a binary command but without args
        for (auto item : binaryCmds)
        {
            if (starts_with(command, item))
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

int HandleBinaryCommand(std::vector<std::string> params)
{
    if (params.front() == "rm")
    {
        cout << "Removed file " << params.back() << endl;
    }
    else if (params.front() == "cp")
    {
        cout << "Copied file" << params.back() << endl;
    }

    return 0;
}