#include "FieldManager.h"

void FieldManager::UpdateFields(string tape)
{
    vector<string> tapeValues = split_with_delim(tape, ',');
    string rowData = "";
    int fieldIndex = 0;
    int offset = 0;

    //Loop over the 3 blocks (of 3 rows)
    for (int b = 0; b < 3; b++)
    {
        //Loop over the 3 columns.
        for (int col = 0; col < 3; col++)
        {
            //Loop over the row.
            for (int row = 0; row < 3; row++)
            {
                //Loop over the sub index.
                for (int sub = 0; sub < 3; sub++)
                {
                    int index = offset + (row * 9 + col * 3 + sub);
                    rowData += tapeValues[index];
                }
            }

            fields[fieldIndex++].Set(rowData);
            rowData = "";
        }

        //Leap the index to the next block.
        offset += 27;
    }

    fields = fields;
}

void FieldManager::Apply(Command command)
{
    //Commands that affect the entire game for both sides.
    if (command.player == "game")
    {
        if (command.key == "field")
        {
            this->UpdateFields(command.value);
        }
    }
}
