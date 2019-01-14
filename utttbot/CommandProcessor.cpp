#include "CommandProcessor.h"

void InvalidCommand(vector<string> input, string message)
{
    cerr << "Invalid command, input: ";

    vector<string>::const_iterator it = input.begin();

    for (; it != input.end(); it++)
    {
        cerr << *it;
    }

    cerr << "... message: " << message << endl;
}

Command CommandProcessor::Process()
{
    string tempLine;
    vector<string> commandInput;

    while (getline(cin, tempLine))
    {
        commandInput = split_with_delim(tempLine, ' ');
        return this->GenerateCommand(commandInput);
    }
}

Command CommandProcessor::GenerateCommand(vector<string> input)
{
    if (input.size() < 1) 
        InvalidCommand(input, "Command too short.");

    //Parse the first part of the command.
    CommandScope type;
    string identifier = input[0].c_str();

    if (identifier == "settings")
    {
        type = CommandScope::Settings;

        if (input.size() != 3)
        {
            InvalidCommand(
                input, 
                "Settings command must at least have 3 params"
            );

            return Command();
        }

        return Command(
            CommandScope::Settings, 
            input[1], 
            input[2]
        );
    }
    else if (identifier == "update")
    {
        type = CommandScope::Update;

        if (input.size() != 4)
        {
            InvalidCommand(
                input,
                "Update command must at least have 4 params"
            );

            return Command();
        }

        return UpdateCommand(
            CommandScope::Update,
            input[1],
            input[2],
            input[3]
        );
    }

    return Command();
}


