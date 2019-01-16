#ifndef FIELDTREE_H
#define FIELDTREE_H

#include "Common.h"
#include "Field.h"

typedef function<int(const Field&)> EvalFunc;
typedef function<vector<Field>(Field)> BranchFunc;


struct FieldNode {
    Field field;
    vector<FieldNode> branches;

    FieldNode(Field field)
    {
        this->field = field;
    }
};

class FieldTree
{
public:
    void Build(FieldNode, int, EvalFunc, BranchFunc);
    Field Prune();

private:
    FieldNode root;
};

#endif