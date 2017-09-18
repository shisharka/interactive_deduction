#include "naturaldeduction.hpp"

/* Natural deduction rules:
0.                                         ------> G, A |- A         (ass)
1.  G, A |- F                              ------>    G |- ~A        (notI)
2.     G |- A; G |- ~A                     ------>    G |- F         (notE)
3.     G |- A; G |- B                      ------>    G |- A /\ B    (conjI)
4.     G |- A /\ B                         ------>    G |- A         (conjE1)
5.     G |- A /\ B                         ------>    G |- B         (conjE2)
6.     G |- A                              ------>    G |- A \/ B    (disjI1)
7.     G |- B                              ------>    G |- A \/ B    (disjI2)
8.     G |- A \/ B; G, A |- C;  G, B |- C  ------>    G |- C         (disjE)
9.  G, A |- B                              ------>    G |- A => B    (impI)
10.    G |- A; G |- A => B                 ------>    G |- B         (impE)
11.    G |- F                              ------>    G |- A         (FalseE)
12.                                        ------>    G |- T         (TrueI)
13.                                        ------>    G |- A \/ ~A   (ExcludedMiddle)
14.    G |- ~~A                            ------>    G |- A         (DoubleNegation)
15.    G |- ~A                             ------>    G |- A         (Contradiction)
*/

bool applyAssumption(vector<Formula> & assumptions, const Formula & f) {
  for(Formula a : assumptions)
    if(f->equalTo(a))
      return true;

  cerr << "Failed to apply assumption" << endl;
  return false;
}

Formula applyNotI(vector<Formula> & assumptions, const Formula & f) {
  if(f->getType() == T_NOT) {
    Formula notOp = ((Not *)f.get())->getOperand();

    bool shouldAdd = true; // indicator for whether or not notOp should be added to assumptions
    for(unsigned i = 0; i < assumptions.size(); i++)
      if(notOp->equalTo(assumptions[i]))
        shouldAdd = false;
    if(shouldAdd)
      assumptions.push_back(notOp);

    return make_shared<False>();
  };

  cerr << "Failed to apply notI" << endl;
  return f;
}

vector<Formula> applyNotE(const Formula & a, const Formula & f) {
  vector<Formula> result = vector<Formula>();

  if(f->getType() == T_FALSE) {
    result.push_back(a);
    // if(a->getType() == T_NOT)
    //   result.push_back(((Not *)a.get())->getOperand());
    // else
      result.push_back(make_shared<Not>(a));

    return result;
  };

  cerr << "Failed to apply notE" << endl;
  result.push_back(f);
  return result;
}

vector<Formula> applyConjI(const Formula & f) {
  vector<Formula> result = vector<Formula>();

  if(f->getType() == T_AND) {
    result.push_back(((And *)f.get())->getOperand1());
    result.push_back(((And *)f.get())->getOperand2());

    return result;
  };

  cerr << "Failed to apply conjI" << endl;
  result.push_back(f);
  return result;
}

Formula applyConjE1(const Formula & a, const Formula & b) {
  return make_shared<And>(a, b);
}

Formula applyConjE2(const Formula & a, const Formula & b) {
  return make_shared<And>(b, a);
}

Formula applyDisjI1(const Formula & f) {
  if(f->getType() == T_OR)
    return (((Or *)f.get())->getOperand1());

  cerr << "Failed to apply disjI1" << endl;
  return f;
}

Formula applyDisjI2(const Formula & f) {
  if(f->getType() == T_OR)
    return (((Or *)f.get())->getOperand2());

  cerr << "Failed to apply disjI2" << endl;
  return f;
}

vector<Formula> applyDisjE(const Formula & c, const Formula & a, const Formula & b) {
  vector<Formula> result = vector<Formula>();
  result.push_back(Formula(new Or(a, b)));
  result.push_back(c);

  return result;
}

Formula applyImpI(vector<Formula> & assumptions, const Formula & f) {
  if(f->getType() == T_IMP) {
    Formula a = (((Imp *)f.get())->getOperand1());
    Formula b = (((Imp *)f.get())->getOperand2());

    bool shouldAdd = true; // indicator for whether or not a should be added to assumptions
    for(unsigned i = 0; i < assumptions.size(); i++)
      if(a->equalTo(assumptions[i]))
        shouldAdd = false;
    if(shouldAdd)
      assumptions.push_back(a);

    return b;
  };

  cerr << "Failed to apply impI" << endl;
  return f;
}

vector<Formula> applyImpE(const Formula & a, const Formula & b) {
  vector<Formula> result = vector<Formula>();

  result.push_back(a);
  result.push_back(make_shared<Imp>(a, b));
  return result;
}

Formula applyFalseE(const Formula & f) {
  return make_shared<False>();
}

bool applyTrueI(Formula & f) {
  return f->getType() == T_TRUE;
}

bool applyExcludedMiddle(Formula & f) {
  if(f->getType() == T_OR) {
    Formula a = (((Or *)f.get())->getOperand1());
    Formula b = (((Or *)f.get())->getOperand2());

    if(a->getType() == T_NOT)
      return b->equalTo((((Not *)a.get())->getOperand()));

    if(b->getType() == T_NOT)
      return a->equalTo((((Not *)b.get())->getOperand()));
  };

  return false;
}

Formula applyDoubleNegation(const Formula & f) {
  return make_shared<Not>(make_shared<Not>(f));
}

Formula applyContradiction(vector<Formula> & assumptions, const Formula & f) {
  Formula fNot = make_shared<Not>(f);
  
  bool shouldAdd = true; // indicator for whether or not fNot should be added to assumptions
  for(unsigned i = 0; i < assumptions.size(); i++)
    if(fNot->equalTo(assumptions[i]))
      shouldAdd = false;
  if(shouldAdd)
    assumptions.push_back(fNot);

  return make_shared<False>();

}
