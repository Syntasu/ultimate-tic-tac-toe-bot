#include "FieldManager.h"

void FieldManager::UpdateFields(string tape)
{
    vector<string> tapeValues = split_with_delim(tape, ',');
    string rowData = "";
    int fieldIndex = 0;

    //Loop over the 3 blocks (of 3 rows)
    for (int block = 0; block < 3; block++)
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
                    int index = (block * 27) + (row * 9 + col * 3 + sub);
                    rowData += tapeValues[index];
                }
            }

            macrofield.SetField(fieldIndex++, rowData);
            cerr << rowData << endl;
            rowData = "";
        }
    }
}

FieldManager::FieldManager()
{
    macrofield = Macrofield();
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
