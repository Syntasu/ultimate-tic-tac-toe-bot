#ifndef SOLVER_H
#define SOLVER_H

#include "Common.h"
#include "Field.h"
#include "Evaluator.h"

class Solver {

    const int SOLVER_MAXIMIZER_WORST = -1000;
    const int SOLVER_MINIMIZER_WORST = 1000;

public:
    Solver();
    void Reset();
    int ProcessMove(Field field);
    vector<Field> Expand(Field);
    int MinimaxSolver(Field field, int depth, bool maximizing);

    int AlphaBetaPruningSolver(
        Field field, int depth, int alpha, int beta, 
        bool maximizing
    );

private:
    int AiBestScore = -999;
    int AiBestMove = -1;
};

#endif
