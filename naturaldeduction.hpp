#ifndef __NATURALDEDUCTION_HPP__
#define __NATURALDEDUCTION_HPP__ 1

#include <deque>
#include <vector>
#include "formula.hpp"

/* Natural deduction rules:
0.                                         ------> G, A |- A         (assumption)
1.  G, A |- F                              ------>    G |- ~A        (notI)
2.     G |- A; G |- ~A                     ------>    G |- F         (notE)
3.     G |- A; G |- B                      ------>    G |- A /\ B    (conjI)
4.     G |- A /\ B                         ------>    G |- A         (conjE1)
5.     G |- A /\ B                         ------>    G |- B         (conjE2)
6.     G |- A /\ B                         ------>    G |- A, B      (conjE)
7.     G |- A                              ------>    G |- A \/ B    (disjI1)
8.     G |- B                              ------>    G |- A \/ B    (disjI2)
9.     G |- A \/ B; G, A |- C;  G, B |- C  ------>    G |- C         (disjE)
10.  G, A |- B                              ------>    G |- A => B    (impI)
11.    G |- A; G |- A => B                 ------>    G |- B         (impE)
12.    G |- F                              ------>    G |- A         (FalseE)
13.                                        ------>    G |- T         (TrueI)
14.                                        ------>    G |- A \/ ~A   (ExcludedMiddle)
15.    G |- A                              ------>    G |- ~~A       (DoubleNegationI)
16.    G |- ~~A                            ------>    G |- A         (DoubleNegationE)
17.    G |- ~A                             ------>    G |- A         (Contradiction)
*/

// Data type for representing goals
typedef pair<vector<Formula>, Formula> Goal;
typedef deque<Goal> Goals;

// --------------------------------- Intuitionistic logic rules ---------------------------------
bool applyAssumption(const Goal & g);

// Introduction rules
void applyNotI(Goal & g);
void applyConjI(const Goal & g, vector<Goal> & subgoals);
void applyDisjI1(Goal & g);
void applyDisjI2(Goal & g);
void applyImpI(Goal & g);
bool applyTrueI(const Goal & g);

// Elimination rules
void applyNotE(Goal & g);
void applyConjE1(Goal & g);
void applyConjE2(Goal & g);
void applyConjE(Goal & g);
void applyDisjE(const Goal & g, vector<Goal> & subgoals);
void applyImpE(const Goal & g, vector<Goal> & subgoals);
void applyFalseE(Goal & g);
// ----------------------------------------------------------------------------------------------

// ------------------------------------ Classical logic rules -----------------------------------
bool applyExcludedMiddle(const Goal & g);
void applyDoubleNegationI(Goal & g);
void applyDoubleNegationE(Goal & g);
void applyContradiction(Goal & g);
// ----------------------------------------------------------------------------------------------

// Function for printing goals
ostream & operator << (ostream & ostr, const Goals & goals);

#endif
