#include "Macrofield.h"

Macrofield::Macrofield() {}

void Macrofield::SetField(int index, string fieldData)
{
    if (index == 0 || index > 9) return;
    fields[index] = Field(fieldData);
}

Field Macrofield::GetField(int index)
{
    if (index == 0 || index > 9) return Field();
    return fields[index];
}

void Macrofield::UpdateField(int index, int move)
{
    //Copy the field and update it.
    Field field = Field(fields[index]);
    field.SetSlot(move, FSSelf);

    //Put it back into the array object.
    fields[index] = field;
}

//Returns a weighted array of the fields contained in the macro board.
array<float, 9> Macrofield::GetNormalizedFieldScores()
{
    array<int, 9> fieldScores;
    array<float, 9> normalizedScores;

    //Get the baseline scores.
    int max = -1000;
    for (int i = 0; i < 9; i++)
    {
        int score = FieldEvaluationFunction(this->fields[i], FSSelf);
        
        if (score < 0)
            score = 0;

        if (score > max)
            max = score;

        fieldScores[i] = score;
    }

    
    for (int i = 0; i < 9; i++)
    {
        float fraction = 0.0f;
        if (max > 0.0f && fieldScores.at(i) > 0.0f)
        {
            //Should return between 0.0 and 1.0.
            fraction = fieldScores[i] / max;
        }
        else
        {
            fraction = 0.0;
        }

        normalizedScores[i] = fraction;
    }

    return normalizedScores;
}

void Macrofield::GetMandatoryField(string input)
{
    int mandatoryField = -2;
    vector<string> values = split_with_delim(input, ',');

    for (int i = 0; i < 9; i++)
    {
        if (values[i] == "-1")
        {
            //Check if this is an "pick it yourself" round.
            if (mandatoryField == -2)
            {
                mandatoryField = -1;
                break;
            }
            else
            {
                mandatoryField = i;
            }
        }
    }

    this->mandatoryField = mandatoryField;
}

void Macrofield::GetSignificantFields(string input)
{
    vector<string> values = split_with_delim(input, ',');

    for (int i = 0; i < 9; i++)
    {
        string c = values.at(i);

        //If either the playing field or undecided field.
        if (c == "-1" || c == ".")
        {
            Field field = GetField(i);

            if (field.IsTerminal())
            {
                significantFields[i] = false;
            }
            else
            {
                significantFields[i] = true;
            }
        }
        else
        {
            significantFields[i] = false;
        }
    }
}
