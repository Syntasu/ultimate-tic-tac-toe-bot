#include "MoveProcessor.h"

MoveProcessor::MoveProcessor(Settings& settings, FieldManager& field)
    : gameSettings(settings), gameField(field), solver(Solver())
{}

int MoveProcessor::GetMoveForField(Field field)
{
    int move = -1;

    if (field.IsTerminal())
        return move;

    if (HasWinner(field))
        return move;

    return solver.ProcessMove(field);
}

string MoveProcessor::ProcessMove()
{
    Vector2 placement;
    Macrofield mfield = gameField.GetMacro();

    if (mfield.mandatoryField < 0)
    {
        this->DoAnyFieldMove();
    }
    else
    {
        Field field = mfield.GetField(mfield.mandatoryField);
        this->DoSpecificFieldMove(mfield.mandatoryField, field);
    }

    stringstream command;
    command << "place_disc ";
    command << placement.x << " ";
    command << placement.y;

    return command.str();
}

Vector2 MoveProcessor::DoAnyFieldMove()
{
    Macrofield mfield = gameField.GetMacro();

    //Get all the field scores (is between 0.0 to 1.0 derived from the highest score).
    array<float, 9> normalizedFields = mfield.GetNormalizedFieldScores();

    //Find the best field that isn't insignificant.
    int bestFieldIndex = -1;
    float bestFieldScore = 0.0f;
    for (int i = 0; i < 9; i++)
    {
        //Filter out any fields that have no use anymore.
        if (!mfield.significantFields.at(i))
        {
            continue;
        }

        if (normalizedFields.at(i) > bestFieldScore)
        {
            bestFieldIndex = i;
            bestFieldScore = normalizedFields.at(i);
        }
    }

    if (bestFieldIndex == -1)
    {
        cerr << "Huh? We failed selecting an field for an open move!" << endl;
        return Vector2();
    }

    //Play out our move.

    //Get our field.
    Field field = mfield.GetField(bestFieldIndex);

    //Find a move for this field.
    int move = this->GetMoveForField(field);

    //Update it the macro board.
    mfield.UpdateField(bestFieldIndex, move);

    return translate_coordinates(bestFieldIndex, move);
}

Vector2 MoveProcessor::DoSpecificFieldMove(int index, Field field)
{   
    //Find a move for this field.
    int move = this->GetMoveForField(field);

    //Update it the macro board.
    this->gameField.GetMacro().UpdateField(index, move);

    return translate_coordinates(index, move);
}

