#include "naturaldeduction.hpp"

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

bool applyAssumption(const set<Formula> & assumptions, const Formula & f) {
  set<Formula>::const_iterator it = assumptions.find(f);
  
  if(it != assumptions.end())
    return true;

  cerr << "Failed to apply assumption" << endl;
  return false;
}

Formula applyNotI(set<Formula> & assumptions, const Formula & f) {
  if(f->getType() == T_NOT) {
    Formula notOp = ((Not *)f.get())->getOperand();

    set<Formula>::const_iterator it = assumptions.find(notOp);
    if(it == assumptions.end())
      assumptions.insert(notOp);

    return make_shared<False>();
  };

  cerr << "Failed to apply notI" << endl;
  return f;
}

set<Formula> applyNotE(const Formula & a, const Formula & f) {
  set<Formula> result = set<Formula>();

  if(f->getType() == T_FALSE) {
    result.insert(a);
    // if(a->getType() == T_NOT)
    //   result.insert(((Not *)a.get())->getOperand());
    // else
      result.insert(make_shared<Not>(a));

    return result;
  };

  cerr << "Failed to apply notE" << endl;
  result.insert(f);
  return result;
}

set<Formula> applyAndI(const Formula & f) {
  set<Formula> result = set<Formula>();

  if(f->getType() == T_AND) {
    result.insert(((And *)f.get())->getOperand1());
    result.insert(((And *)f.get())->getOperand2());

    return result;
  };

  cerr << "Failed to apply andI" << endl;
  result.insert(f);
  return result;
}

Formula applyAndE1(const Formula & a, const Formula & b) {
  return make_shared<And>(a, b);
}

Formula applyAndE2(const Formula & a, const Formula & b) {
  return make_shared<And>(b, a);
}

Formula applyOrI1(const Formula & f) {
  if(f->getType() == T_OR)
    return (((Or *)f.get())->getOperand1());

  cerr << "Failed to apply orI1" << endl;
  return f;
}

Formula applyOrI2(const Formula & f) {
  if(f->getType() == T_OR)
    return (((Or *)f.get())->getOperand2());

  cerr << "Failed to apply orI2" << endl;
  return f;
}

set<Formula> applyOrE(const Formula & c, const Formula & a, const Formula & b) {
  set<Formula> result = set<Formula>();
  result.insert(Formula(new Or(a, b)));
  result.insert(c);

  return result;
}

Formula applyImpI1(set<Formula> & assumptions, const Formula & f) {
  if(f->getType() == T_IMP) {
    Formula a = (((Imp *)f.get())->getOperand1());
    Formula b = (((Imp *)f.get())->getOperand2());

    set<Formula>::const_iterator it = assumptions.find(a);
    if(it == assumptions.end())
      assumptions.insert(a);

    return b;
  };

  cerr << "Failed to apply impI" << endl;
  return f;
}

set<Formula> applyImpE(const Formula & a, const Formula & b) {
  set<Formula> result = set<Formula>();

  result.insert(a);
  result.insert(make_shared<Imp>(a, b));
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

Formula applyContradiction(set<Formula> & assumptions, const Formula & f) {
  Formula fNot = make_shared<Not>(f);
  
  set<Formula>::const_iterator it = assumptions.find(fNot);
  if(it == assumptions.end())
    assumptions.insert(fNot);

  return make_shared<False>();

}
