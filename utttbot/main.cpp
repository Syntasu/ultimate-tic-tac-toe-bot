#include "CommandProcessor.h"
#include "utttbot.h"
#include "Settings.h"

#define IS_LOCAL_MACHINE 1


int main() 
{
    //Create a pointer to the game settings class/container.
    Settings* settings = &Settings();

    //Loop the processing.
    while (true) {
        CommandProcessor cmdproc = CommandProcessor();
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

        UTTTBot bot;
        bot.run();
    }

	return 0;
}


