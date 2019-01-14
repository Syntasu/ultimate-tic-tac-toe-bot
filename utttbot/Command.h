#ifndef COMMAND_HDR
#define COMMAND_HDR

#include "Common.h"

enum CommandScope {
    Invalid,
    Settings,
    Update,
};

inline const char* CommandScopeStr(CommandScope scope)
{
    switch (scope) {
        case Invalid: return "Invalid";
        case Settings: return "Settings";
        case Update: return "Update";
        default: return "CommandScopeUnk";
    }
}

struct Command {
    CommandScope scope;
    string key;
    string value;

    Command() 
    {
        this->scope = CommandScope::Invalid;
    }

    Command(CommandScope scope, string key, string value) 
    {
        this->scope = scope;
        this->key = key;
        this->value = value;
    }
};

struct UpdateCommand : public Command {
    string player;

    UpdateCommand(CommandScope scope, string key, string value, string player)
    {
        this->scope = scope;
        this->key = key;
        this->value = value;
        this->player = player;
    }
};

inline ostream& operator << (ostream& os, const Command& cmd)  
{
    os  << CommandScopeStr(cmd.scope)
        << ", "
        << cmd.key
        << ", "
        << cmd.value
        << endl;

    return os;
}

inline ostream& operator << (ostream& os, const UpdateCommand& cmd)
{
    os << CommandScopeStr(cmd.scope)
        << ", "
        << cmd.key
        << ", "
        << cmd.value
        << ", "
        << cmd.player
        << endl;

    return os;
}

#endif