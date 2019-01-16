#include "Evaluator.h"
/*
    Evaluating row, columns and diagonals.:
        0 0 0 -> Empty, we don't care.
        0 0 o -> Opponent has ownership, two steps away
        0 o o -> Opponent has ownership, one step away.
        0 0 x -> Player has ownership, two steps away
        0 x x -> Player has ownership, one step away.
        0 x o -> Mixed row, this is a draw.
        x o x -> Mixed row, this is a draw.
        o o x -> Etc.
*/
const int EVAL_ONE_STEP_AWAY = 10;
const int EVAL_TWO_STEP_AWAY = 5;
const int EVAL_INSIGNIFICANT = 0;

//TODO: Implement some functions that determines the consecutiveness of an
//      array based on value, so we don't have to run same logic over and over again.
//      

inline int EvaluateRowCol(Field& field, FieldStates& perspective)
{
    int field_score = 0;
    FieldStates row_currentOwner = FieldStates::FSEmpty;
    FieldStates col_currentOwner = FieldStates::FSEmpty;

    int row_steps = 0;
    int col_steps = 0;

    bool is_row_invalid = false;
    bool is_col_invalid = false;

    for (int n = 0; n < 3; n++)
    {
        for (int sub = 0; sub < 3; sub++)
        {
            //Get the owner of this slot.
            FieldStates row_owner = field.GetSlot(n * 3 + sub);
            FieldStates col_owner = field.GetSlot(sub * 3 + n);

            //Process the row owner stuff, check for mixed rows.
            if (row_owner != FSEmpty && !is_row_invalid)
            {
                if (row_currentOwner == FSEmpty)
                {
                    row_currentOwner = row_owner;
                    row_steps++;
                }
                else
                {
                    if (row_owner != row_currentOwner)
                    {
                        is_row_invalid = true;
                    }
                    else
                    {
                        row_steps++;
                    }
                }
            }

            //Process the col owner stuff, check for mixed cols.
            if (col_owner != FSEmpty && !is_col_invalid)
            {
                if (col_currentOwner == FSEmpty)
                {
                    col_currentOwner = col_owner;
                    col_steps++;
                }
                else
                {
                    if (col_owner != col_currentOwner)
                    {
                        is_col_invalid = true;
                    }
                    else
                    {
                        col_steps++;
                    }
                }
            }
        }
        
        //Process the score of all the rows.
        if (!is_row_invalid && row_currentOwner != FSEmpty)
        {
            int row_score = 0;
            int steps = 3 - row_steps;

            row_score += steps <= 1 ? EVAL_ONE_STEP_AWAY : EVAL_TWO_STEP_AWAY;
            field_score += row_currentOwner == perspective ? row_score : -row_score;
        }

        //Process the score of the columns.
        if (!is_col_invalid && col_currentOwner != FSEmpty)
        {
            int col_score = 0;
            int steps = 3 - col_steps;

            col_score += steps <= 1 ? EVAL_ONE_STEP_AWAY : EVAL_TWO_STEP_AWAY;
            field_score += col_currentOwner == perspective ? col_score : -col_score;
        }

        //Reset all the things!
        is_row_invalid = false;
        is_col_invalid = false;
        row_currentOwner = FSEmpty;
        col_currentOwner = FSEmpty;
        row_steps = 0;
        col_steps = 0;
    }

    return field_score;
}

inline int EvaluateDiagonals(Field& field, FieldStates& perspective)
{
    array<FieldStates, 3> diagonalTLRB = {
        field.GetSlot(0),
        field.GetSlot(4),
        field.GetSlot(8)
    };

    array<FieldStates, 3> diagonaTRBL = {
        field.GetSlot(2),
        field.GetSlot(4),
        field.GetSlot(6)
    };

    int diagonal_score = 0;
    FieldStates fieldOwner_tlrb = FSEmpty;
    FieldStates fieldOwner_trbl = FSEmpty;

    int tlrb_steps = 0;
    int trbl_steps = 0;

    bool tlrb_invalid = false;
    bool trbl_invalid = false;

    for (int i = 0; i < 3; i++)
    {
        FieldStates owner_tlrb = diagonalTLRB[i];
        FieldStates owner_trbl = diagonaTRBL[i];

        if (owner_tlrb != FSEmpty && !tlrb_invalid)
        {
            if (fieldOwner_tlrb == FSEmpty)
            {
                fieldOwner_tlrb = owner_tlrb;
                tlrb_steps++;
            }
            else
            {
                if (fieldOwner_tlrb != owner_tlrb)
                {
                    tlrb_invalid = true;
                }
                else
                {
                    tlrb_steps++;
                }
            }
        }

        if (owner_trbl != FSEmpty && !trbl_invalid)
        {
            if (fieldOwner_trbl == FSEmpty)
            {
                fieldOwner_trbl = owner_trbl;
                trbl_steps++;
            }
            else
            {
                if (fieldOwner_trbl != owner_trbl)
                {
                    trbl_invalid = true;
                }
                else
                {
                    trbl_steps++;
                }
            }
        }
    }

    //Process the score of all the rows.
    if (!tlrb_invalid && fieldOwner_tlrb != FSEmpty)
    {
        int tlrb_score = 0;
        int steps = 3 - tlrb_steps;

        tlrb_score += steps <= 1 ? EVAL_ONE_STEP_AWAY : EVAL_TWO_STEP_AWAY;
        diagonal_score += fieldOwner_tlrb == perspective ? tlrb_score : -tlrb_score;
    }

    //Process the score of all the rows.
    if (!tlrb_invalid && fieldOwner_tlrb != FSEmpty)
    {
        int tlrb_score = 0;
        int steps = 3 - tlrb_steps;

        tlrb_score += steps <= 1 ? EVAL_ONE_STEP_AWAY : EVAL_TWO_STEP_AWAY;
        diagonal_score += fieldOwner_tlrb == perspective ? tlrb_score : -tlrb_score;
    }

    //Reset all the things!
    trbl_invalid = false;
    tlrb_invalid = false;
    fieldOwner_trbl = FSEmpty;
    fieldOwner_tlrb = FSEmpty;
    tlrb_steps = 0;
    trbl_steps = 0;

    return diagonal_score;
}

//NOTE: Perspective means how this code is going to distinguish between player or enemy.
//      Based on the field states.
int FieldEvaluationFunction(Field field, FieldStates perspective)
{
    //Is the field empty?
    if (field.IsEmpty())
        return EVAL_INSIGNIFICANT;

    //Is the field terminal?
    if (field.IsTerminal())
        return EVAL_INSIGNIFICANT;

    int score = 
        EvaluateRowCol(field, perspective) + 
        EvaluateDiagonals(field, perspective);

    return score;
}

vector<Field> FieldBranchingFunction(Field baseField)
{
    vector<Field> mutatedFields;
    FieldStates currentPlayer = baseField.GetPlayerTurn();
    vector<int> valid_slots = baseField.GetPlayableSlots();

    //Generate all the valid moves.
    vector<int>::const_iterator it = valid_slots.begin();

    //Play one move on all the boards.
    for (int i = 0; i < valid_slots.size(); i++)
    {
        Field mutatedField = baseField;
        mutatedField.SetSlot(valid_slots[i], currentPlayer);
        mutatedField.score = FieldEvaluationFunction(mutatedField, FSSelf);

        mutatedFields.push_back(mutatedField);
    }

    return mutatedFields;
}
