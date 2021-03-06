# Interactive Theorem Proof Assistant for Natural Deduction

Console application implemented in C++, using flex and bison for syntax checking and parsing of the input formula.<br /><br />
Input should be in mathematical notation, for example: ```~(a \/ b) => ~a /\ ~b``` <br />
After parsing of the input formula, user interactively selects which rule to apply.<br />
In each step user has a list of goals. Goal has a set of assumptions on the left side and a single formula on the right side.
Selected rule is applied to the first goal from the list.<br />
Theorem is proved when the list of goals gets empty.

### Deduction rules:
```
// Intuitionistic deduction:
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
10. G, A |- B                              ------>    G |- A => B    (impI)
11.    G |- A; G |- A => B                 ------>    G |- B         (impE)
12.    G |- F                              ------>    G |- A         (FalseE)
13.                                        ------>    G |- T         (TrueI)

// Classical deduction:
14.                                        ------>    G |- A \/ ~A   (ExcludedMiddle)
15.    G |- A                              ------>    G |- ~~A       (DoubleNegationI)
16.    G |- ~~A                            ------>    G |- A         (DoubleNegationE)
17.    G |- ~A                             ------>    G |- A         (Contradiction)
```
