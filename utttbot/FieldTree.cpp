#include "FieldTree.h"

FieldTree::FieldTree(FieldStates perspective)
{
    this->perspective = perspective;
}

//Builds the field tree for you to n depth.
//Note: having depth set too high will exhaust the timebank.
//      since this will scale quite exponentially -- O(n^2)!
void FieldTree::Build(
    FieldNode* node, int depth, EvalFunc eval, BranchFunc branch)
{
    //If this is the first occurrence we are handling...
    //  Then signify that this is our root node.
    if (!hasRoot)
    {
        root = node;
        hasRoot = true;
    }

    //we reached the end of the tree we want to build up to a certain depth.
    if (depth == 0) return;

    //Get and assign the score of this field.
    node->field.score = eval(node->field, this->perspective);

    //We cannot expand terminal nodes.
    if (node->field.IsTerminal())
        return;

    //Based on "node.field" (this node) we want to branch outwards.
    //  This is done by making a mutation to the current field.
    vector<Field> branches = branch(node->field);
    vector<Field>::const_iterator it = branches.cbegin();
    FieldNode* newField = nullptr;

    //Tell all our mutated fields to also build a tree themselves.
    for (;it != branches.end(); it++)
    {
        FieldNode* mutatedNode = new FieldNode(*it);
        this->Build(mutatedNode, depth - 1, eval, branch);

        node->branches.push_back(mutatedNode);
    }
}

//a-b prune the tree we've just built.
Field FieldTree::Prune()
{
    return Field();
}



