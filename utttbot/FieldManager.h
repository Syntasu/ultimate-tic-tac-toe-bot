#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include "Common.h"
#include "Command.h"
#include "Field.h"

class FieldManager
{
public:
    void Apply(Command command);

private:
    array<Field, 9> fields;

    void UpdateFields(string values);
};

#endif
