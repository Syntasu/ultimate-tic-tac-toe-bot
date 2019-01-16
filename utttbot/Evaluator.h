#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Common.h"
#include "Field.h"

int FieldEvaluationFunction(Field field, FieldState perspective);
vector<Field> FieldBranchingFunction(Field baseField);

#endif