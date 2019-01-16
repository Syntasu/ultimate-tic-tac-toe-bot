#ifndef FIELD_H
#define FIELD_H

#include "Common.h"

enum FieldStates {
    FSEmpty,
    FSSelf,
    FSOpponent,
};

struct Field {

    int score;
    array<FieldStates, 9> fieldSlots; 

    Field() {
        //Reset the field.
        for (int i = 0; i < 9; i++)
        {
            fieldSlots[i] = FieldStates::FSEmpty;
        }

        score = 0;
    }

    Field(string data)
    {
        Set(data);
    }

    inline void SetSlot(int index, FieldStates state)
    {
        if (index > 9 || index < 0)
        {
            cerr << "Trying to set slot of a field out of bounds: "
                << index 
                << endl;
            return;
        }

        fieldSlots[index] = state;
    }

    inline FieldStates GetSlot(int index)
    {
        if (index > 9 || index < 0)
        {
            cerr << "Trying to set slot of a field out of bounds: "
                << index
                << endl;
            return FieldStates::FSEmpty;
        }

        return fieldSlots[index];
    }

    void Set(string tape)
    {
        if (tape.size() < 9) {
            cerr << "Input tape must be 9 values!";
            return;
        }
      
        for (int i = 0; i < 9; i++)
        {
            char tapeValue = tape[i];

            switch (tapeValue)
            {
            case '.': SetSlot(i, FieldStates::FSEmpty); break;
            case '0': SetSlot(i, FieldStates::FSOpponent); break;
            case '1': SetSlot(i, FieldStates::FSSelf); break;
            }
        }
    }

    inline bool IsTerminal()
    {
        for (int i = 0; i < 9; i++)
        {
            if (fieldSlots[i] == FieldStates::FSEmpty)
                return false;
        }

        return true;
    }

    inline bool IsEmpty()
    {
        for (int i = 0; i < 9; i++)
        {
            if (fieldSlots[i] != FieldStates::FSEmpty)
                return false;
        }

        return true;
    }

};

#endif