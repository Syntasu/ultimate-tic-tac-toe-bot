#include "CommandProcessor.h"
#include "MoveProcessor.h"
#include "FieldManager.h"
#include "Settings.h"
#include "FieldTree.h"
#include "Evaluator.h"
#include "Solver.h"

void HandleSettingsCommand(Settings&, Command);
void HandleUpdateCommand(FieldManager&, Command);
void HandleActionCommand(MoveProcessor&, Command);
void HandleInvalidCommand(Command);
void HandleAnyCommand(Command);
void HandleUnknownCommand(Command);

int main() 
{
    Solver solver = Solver();

    Field field = Field(".11110010");
    solver.Reset();
    int bestMove = solver.GetOptimalMove(field);
    if (bestMove > 0)
    {
        FieldState state = field.GetPlayerTurn();
        field.SetSlot(bestMove, state);
    }
    else

    {
        cerr << "Failed to get move";
    }
    cin.get();




    ////Reference to our classes.
    //Settings settings = Settings();
    //FieldManager fieldManager = FieldManager();

    //MoveProcessor moveProc = MoveProcessor(settings, fieldManager);
    //CommandProcessor cmdproc = CommandProcessor();

    //Command cmd = cmdproc.Process();

    ////The command is anything but invalid... then log it.
    //if (cmd.scope != CommandScope::CmdScopeInvalid)
    //    HandleAnyCommand(cmd);

    //switch (cmd.scope)
    //{
    //case CmdScopeInvalid:  HandleInvalidCommand(cmd); break;
    //case CmdScopeAction:   HandleActionCommand(moveProc, cmd); break;
    //case CmdScopeSettings: HandleSettingsCommand(settings, cmd); break;
    //case CmdScopeUpdate:   HandleUpdateCommand(fieldManager, cmd); break;
    //default:               HandleUnknownCommand(cmd);
    //}

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

void HandleActionCommand(MoveProcessor& moveProc, Command cmd)
{
    string move = moveProc.ProcessMove();
    cout << move;
}

void HandleSettingsCommand(Settings& settings, Command cmd)
{
    settings.Apply(cmd);
}

void HandleUpdateCommand(FieldManager& fieldManager, Command cmd)
{
    fieldManager.Apply(cmd);
}