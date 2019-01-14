#include "CommandProcessor.h"
#include "utttbot.h"

#define IS_LOCAL_MACHINE 1

int main() 
{
    
#if IS_LOCAL_MACHINE
    //Loop the processing.
    while (true) {
#endif
        CommandProcessor cmdproc = CommandProcessor();
        Command cmd = cmdproc.Process();

        if (cmd.scope != CommandScope::Invalid)
        {
            cerr << "Received command: " << cmd;
        }

        UTTTBot bot;
        bot.run();

#if IS_LOCAL_MACHINE
    }
#endif
	
	return 0;
}


