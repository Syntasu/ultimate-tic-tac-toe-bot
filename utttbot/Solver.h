#ifndef SOLVER_H
#define SOLVE_H

#include "Common.h"
#include "Field.h"
#include "Evaluator.h"

class Solver {

    const int SOLVER_MAXIMIZER_WORST = -1000;
    const int SOLVER_MINIMIZER_WORST = 1000;

public:
    void Reset();
    int GetOptimalMove(Field field);
    vector<Field> Expand(Field);
    int MinimaxSolver(Field field, int depth, bool maximizing);
    int AlphaBetaPruningSolver(Field field, int depth, int alpha, int beta, bool maximizing);

private:
    int AiBestScore = -1;
    int AiBestMove = -1;
};

#endif