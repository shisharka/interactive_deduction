#ifndef __NATURALDEDUCTION_HPP__
#define __NATURALDEDUCTION_HPP__ 1

#include "formula.hpp"

/* Natural deduction rules:
0.                                         ------> G, A |- A         (ass)
1.  G, A |- F                              ------>    G | -~A        (notI)
2.     G |- A; G |- ~A                     ------>    G |- F         (notE)
3.     G |- A; G |- B                      ------>    G |- A /\ B    (andI)
4.     G |- A /\ B                         ------>    G |- A         (andE1)
5.     G |- A /\ B                         ------>    G |- B         (andE2)
6.     G |- A                              ------>    G |- A \/ B    (orI1)
7.     G |- B                              ------>    G |- A \/ B    (orI2)
8.     G |- A \/ B; G, A |- C;  G, B |- C  ------>    G |- C         (orE)
9.  G, A |- B                              ------>    G |- A => B    (impI)
10.    G |- A; G |- A => B                 ------>    G |- B         (impE)
11.    G |- F                              ------>    G |- A         (FalseE)
12.                                        ------>    G |- T         (TrueI)
13.                                        ------>    G |- A \/ ~A   (ExcludedMiddle)
14.    G |- ~~A                            ------>    G |- A         (DoubleNegation)
15.    G |- ~A                             ------>    G |- A         (Contradiction)
*/

bool applyAssumption(const set<Formula> & assumptions, const Formula & f);

Formula applyNotI(set<Formula> & assumptions, const Formula & f);

set<Formula> applyNotE(const Formula & a, const Formula & f);

set<Formula> applyAndI(const Formula & f);

Formula applyAndE1(const Formula & a, const Formula & b);

Formula applyAndE2(const Formula & a, const Formula & b);

Formula applyOrI1(const Formula & f);

Formula applyOrI2(const Formula & f);

set<Formula> applyOrE(const Formula & c, const Formula & a, const Formula & b);

Formula applyImpI1(set<Formula> & assumptions, const Formula & f);

set<Formula> applyImpE(const Formula & a, const Formula & b);

Formula applyFalseE(const Formula & f);

bool applyTrueI(Formula & f);

bool applyExcludedMiddle(Formula & f);

Formula applyDoubleNegation(const Formula & f);

Formula applyContradiction(set<Formula> & assumptions, const Formula & f);

#endif
