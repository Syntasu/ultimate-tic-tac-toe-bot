#include "CommandProcessor.h"
#include "utttbot.h"
#include "FieldManager.h"
#include "Settings.h"

void HandleSettingsCommand(Settings&, Command);
void HandleUpdateCommand(FieldManager&, Command);
void HandleActionCommand(Command);
void HandleInvalidCommand(Command);
void HandleAnyCommand(Command);
void HandleUnknownCommand(Command);

int main() 
{
    //Reference to our classes.
    Settings settings = Settings();
    FieldManager fieldManager = FieldManager();
    CommandProcessor cmdproc = CommandProcessor();

    while (true)
    {
        Command cmd = cmdproc.Process();

        //The command is anything but invalid... then log it.
        if (cmd.scope != CommandScope::CmdScopeInvalid)
            HandleAnyCommand(cmd);

        switch (cmd.scope)
        {
        case CmdScopeInvalid:  HandleInvalidCommand(cmd); break;
        case CmdScopeAction:   HandleActionCommand(cmd); break;
        case CmdScopeSettings: HandleSettingsCommand(settings, cmd); break;
        case CmdScopeUpdate:   HandleUpdateCommand(fieldManager, cmd); break;
        default:               HandleUnknownCommand(cmd);
        }
    }

	return 0;
}

void HandleInvalidCommand(Command cmd) 
{
    cerr << "HandleInvalidCommnad: Received -> " << cmd;
}

void HandleUnknownCommand(Command cmd)
{
    cerr << "HandleUnknownCommand: Received command is unknown -> " << cmd;
}

void HandleAnyCommand(Command cmd)
{
    cerr << "HandleAnyCommand: Received -> " << cmd;
}

void HandleActionCommand(Command cmd)
{
    cerr << "HandleActionCommand: " << cmd;
}

void HandleSettingsCommand(Settings& settings, Command cmd)
{
    settings.Apply(cmd);
}

void HandleUpdateCommand(FieldManager& fieldManager, Command cmd)
{
    fieldManager.Apply(cmd);
}