#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include "Common.h"
#include "Command.h"
#include "Macrofield.h"

class FieldManager
{
public:
    FieldManager();
    void Apply(Command command);

private:
    Macrofield macrofield;
    void RedefineFields(string values);
};

#endif
