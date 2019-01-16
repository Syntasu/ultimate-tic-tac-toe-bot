#ifndef FIELDTREE_H
#define FIELDTREE_H

#include "Common.h"
#include "Field.h"

typedef function<int(const Field&, FieldState)> EvalFunc;
typedef function<vector<Field>(Field)> BranchFunc;


struct FieldNode {
    Field field;
    vector<FieldNode*> branches;
    
    FieldNode() {}

    FieldNode(Field field)
    {
        this->field = field;
    }
};

class FieldTree
{
public:
    FieldTree(FieldState);
    FieldNode* GetRoot();

private:

    FieldState perspective;
    FieldNode* root;
    bool hasRoot = false;
};

#endif