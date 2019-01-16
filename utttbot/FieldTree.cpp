#include "FieldTree.h"

FieldTree::FieldTree(FieldState perspective)
{
    this->perspective = perspective;
}

FieldNode* FieldTree::GetRoot()
{
    return this->root;
}
