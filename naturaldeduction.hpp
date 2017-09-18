#ifndef __NATURALDEDUCTION_HPP__
#define __NATURALDEDUCTION_HPP__ 1

#include <vector>
#include "formula.hpp"

/* Natural deduction rules:
0.                                         ------> G, A |- A         (ass)
1.  G, A |- F                              ------>    G | -~A        (notI)
2.     G |- A; G |- ~A                     ------>    G |- F         (notE)
3.     G |- A; G |- B                      ------>    G |- A /\ B    (conjI)
4.     G |- A /\ B                         ------>    G |- A         (conjE1)
5.     G |- A /\ B                         ------>    G |- B         (conjE2)
6.     G |- A                              ------>    G |- A \/ B    (disjI1)
7.     G |- B                              ------>    G |- A \/ B    (disjI2)
8.     G |- A \/ B; G, A |- C;  G, B |- C  ------>    G |- C         (disjE)
9.  G, A |- B                              ------>    G |- A => B    (impI)
10.    G |- A; G |- A => B                 ------>    G |- B         (impE)
11.    G |- F                              ------>    G |- A         (falseE)
12.                                        ------>    G |- T         (trueI)
13.                                        ------>    G |- A \/ ~A   (ExcludedMiddle)
14.    G |- ~~A                            ------>    G |- A         (DoubleNegation)
15.    G |- ~A                             ------>    G |- A         (Contradiction)
*/

bool applyAssumption(vector<Formula> & assumptions, const Formula & f);

Formula applyNotI(vector<Formula> & assumptions, const Formula & f);

vector<Formula> applyNotE(const Formula & a, const Formula & f);

vector<Formula> applyConjI(const Formula & f);

Formula applyConjE1(const Formula & a, const Formula & b);

Formula applyConjE2(const Formula & a, const Formula & b);

Formula applyDisjI1(const Formula & f);

Formula applyDisjI2(const Formula & f);

vector<Formula> applyDisjE(const Formula & c, const Formula & a, const Formula & b);

Formula applyImpI(vector<Formula> & assumptions, const Formula & f);

vector<Formula> applyImpE(const Formula & a, const Formula & b);

Formula applyFalseE(const Formula & f);

bool applyTrueI(Formula & f);

bool applyExcludedMiddle(Formula & f);

Formula applyDoubleNegation(const Formula & f);

Formula applyContradiction(vector<Formula> & assumptions, const Formula & f);

#endif
