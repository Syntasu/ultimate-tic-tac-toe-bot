#ifndef MACROFIELD_H
#define MACROFIELD_H

#include "Common.h"
#include "Field.h"

struct Macrofield
{
    array<Field, 9> fields;

    void SetField(int index, string fieldData);
};

#endif