#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Common.h"
#include "Field.h"

int FieldEvaluationFunction(Field field, FieldStates perspective);
vector<Field> FieldBranchingFunction(Field baseField);

#endif