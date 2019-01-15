#include "CommandProcessor.h"
#include "utttbot.h"
#include "FieldManager.h"
#include "Settings.h"

int main() 
{
    //Create a pointer to the game settings class/container.
    Settings* settings = &Settings();
    
    //Pointer to the field manager.
    FieldManager* fieldManager = &FieldManager();

    CommandProcessor cmdproc = CommandProcessor();

    while (true)
    {
        Command cmd = cmdproc.Process();

        //Log any command we receive.
        if (cmd.scope != CommandScope::CmdScopeInvalid)
        {
            cerr << "Received command: " << cmd;
        }

        if (cmd.scope == CommandScope::CmdScopeSettings)
        {
            settings->Apply(cmd);
        }

        if (cmd.scope == CommandScope::CmdScopeUpdate)
        {

        }
    }
    //UTTTBot bot;
    //bot.run();

	return 0;
}

