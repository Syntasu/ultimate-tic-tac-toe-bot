#include "MoveProcessor.h"


MoveProcessor::MoveProcessor(Settings& settings, FieldManager& field)
    : gameSettings(settings), gameField(field)
{}

string MoveProcessor::ProcessMove()
{
    return "place_disc 0 0";
}
