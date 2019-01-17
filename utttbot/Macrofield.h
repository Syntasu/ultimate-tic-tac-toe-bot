#ifndef MACROFIELD_H
#define MACROFIELD_H

#include "Common.h"

#include "Field.h"
#include "Evaluator.h"

struct Macrofield
{
    array<Field, 9> fields;
    array<bool, 9> significantFields;
    int mandatoryField = -1;

    void SetField(int index, string fieldData);
    Field GetField(int index);
    void UpdateField(int index, int move);

    array<float, 9> GetNormalizedFieldScores();

    void GetMandatoryField(string input);
    void GetSignificantFields(string input);
};

#endif