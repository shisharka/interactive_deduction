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
14.    G |- A                              ------>    G |- ~~A       (DoubleNegationI)
15.    G |- ~~A                            ------>    G |- A         (DoubleNegationE)
16.    G |- ~A                             ------>    G |- A         (Contradiction)
*/

// Helper function
void addAssumption(vector<Formula> & assumptions, const Formula & f) {
  bool shouldAdd = true; // indicator for whether or not f should be added to assumptions
  for(unsigned i = 0; i < assumptions.size(); i++)
    if(f->equalTo(assumptions[i]))
      shouldAdd = false;
  if(shouldAdd)
    assumptions.push_back(f);
}

bool applyAssumption(const Goal & g) {
  for(Formula a : g.first)
    if(g.second->equalTo(a))
      return true;

  cerr << "Failed to apply assumption" << endl;
  return false; 
}

void applyNotI(Goal & g) {
  if(g.second->getType() == T_NOT) {
    Formula notOp = ((Not *)g.second.get())->getOperand();

    addAssumption(g.first, notOp);

    g.second = make_shared<False>();
  }
  else
    cerr << "Failed to apply notI" << endl;
}

void applyConjI(const Goal & g, vector<Goal> & subgoals) {
  if(g.second->getType() == T_AND) {
    Goal goal1, goal2;

    goal1.first = g.first;
    goal1.second = ((And *)g.second.get())->getOperand1();

    goal2.first = g.first;
    goal2.second = ((And *)g.second.get())->getOperand2();

    subgoals.push_back(goal1);
    subgoals.push_back(goal2);
  }
  else
    cerr << "Failed to apply conjI" << endl;
}

void applyDisjI1(Goal & g) {
  if(g.second->getType() == T_OR)
    g.second = (((Or *)g.second.get())->getOperand1());
  else
    cerr << "Failed to apply disjI1" << endl;
}

void applyDisjI2(Goal & g) {
  if(g.second->getType() == T_OR)
    g.second = (((Or *)g.second.get())->getOperand2());
  else
    cerr << "Failed to apply disjI1" << endl;
}

void applyImpI(Goal & g) {
  if(g.second->getType() == T_IMP) {
    Formula a = (((Imp *)g.second.get())->getOperand1());
    Formula b = (((Imp *)g.second.get())->getOperand2());

    addAssumption(g.first, a);

    g.second = b;
  }
  else
    cerr << "Failed to apply impI" << endl;
}

bool applyTrueI(const Goal & g) {
  if(g.second->getType() == T_TRUE)
    return true;
  else {
    cerr << "Failed to apply trueI" << endl;
    return false;
  }
}

void applyNotE(Goal & g) {
  for(vector<Formula>::iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_NOT) {
      Formula f = ((Not *)(*i).get())->getOperand();
      g.first.erase(i);
      g.second = f;
      return;
    };
  };

  cerr << "Failed to apply notE" << endl;
}

void applyConjE1(Goal & g) {
  for(vector<Formula>::iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_AND) {
      Formula f = ((And *)(*i).get())->getOperand1();
      g.first.erase(i);
      addAssumption(g.first, f);
      return;
    };
  };

  cerr << "Failed to apply conjE1" << endl;
}

void applyConjE2(Goal & g) {
  for(vector<Formula>::iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_AND) {
      Formula f = ((And *)(*i).get())->getOperand2();
      g.first.erase(i);
      addAssumption(g.first, f);
      return;
    };
  };

  cerr << "Failed to apply conjE2" << endl;
}

void applyDisjE(const Goal & g, vector<Goal> & subgoals) {
  Formula a, b;
  vector<Formula> ass1, ass2;
  bool applied = false;

  for(vector<Formula>::const_iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_OR && !applied) {
      a = ((Or *)(*i).get())->getOperand1();
      b = ((Or *)(*i).get())->getOperand2();
      applied = true;
    }
    else {
      ass1.push_back(*i);
      ass2.push_back(*i);
    };
  };

  if(applied) {
    addAssumption(ass1, a);
    addAssumption(ass2, b);
    subgoals.push_back(make_pair(ass1, g.second));
    subgoals.push_back(make_pair(ass2, g.second));
  }
  else
    cerr << "Failed to apply disjE" << endl;
}

void applyImpE(const Goal & g, vector<Goal> & subgoals) {
  Formula a, b;
  vector<Formula> ass1, ass2;
  bool applied = false;

  for(vector<Formula>::const_iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_IMP && !applied) {
      a = ((Imp *)(*i).get())->getOperand1();
      b = ((Imp *)(*i).get())->getOperand2();
      applied = true;
    }
    else {
      addAssumption(ass1, *i);
      addAssumption(ass2, *i);
    };
  };

  if(applied) {
    addAssumption(ass2, b);
    subgoals.push_back(make_pair(ass1, a));
    subgoals.push_back(make_pair(ass2, g.second));
  }
  else
    cerr << "Failed to apply impE" << endl;
}

void applyFalseE(Goal & g) {
  for(vector<Formula>::iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_FALSE) {
      g.first.erase(i);
      addAssumption(g.first, g.second);
      return;
    };
  };

  cerr << "Failed to apply falseE" << endl;
}

bool applyExcludedMiddle(const Goal & g) {
  if(g.second->getType() == T_OR) {
    Formula a = ((Or *)g.second.get())->getOperand1();
    Formula b = ((Or *)g.second.get())->getOperand1();
    if(a->getType() == T_NOT && ((Not *)a.get())->getOperand()->equalTo(b))
      return true;
    if(b->getType() == T_NOT && ((Not *)b.get())->getOperand()->equalTo(a))
      return true;
  };

  cerr << "Failed to apply ExcludedMiddle" << endl;
  return false; 
}

void applyDoubleNegationI(Goal & g) {
  if(g.second->getType() == T_NOT && ((Not *)(g.second.get()))->getOperand()->getType() == T_NOT)
    g.second = ((Not*)((Not *)(g.second.get()))->getOperand().get())->getOperand();
  else
    cerr << "Failed to apply DoubleNegationI" << endl;
}

void applyDoubleNegationE(Goal & g) {
  for(vector<Formula>::iterator i = g.first.begin(); i != g.first.end(); i++) {
    if((*i)->getType() == T_NOT && ((Not *)((*i).get()))->getOperand()->getType() == T_NOT) {
      (*i) = ((Not*)((Not *)((*i).get()))->getOperand().get())->getOperand();
      return;
    };
  };

  cerr << "Failed to apply DoubleNegationE" << endl;
}

void applyContradiction(Goal & g) {
  addAssumption(g.first, make_shared<Not>(g.second));
  g.second = make_shared<False>();
}

// Function for printing goals
ostream & operator << (ostream & ostr, const Goals & goals) {
  ostr << endl << "Goals:" << endl;
  for(unsigned i = 0; i < goals.size(); i++) {
    ostr << i + 1 << ". ";
    for(unsigned j = 0; j < goals[i].first.size(); j++) {
      ostr << goals[i].first[j];
      if(j < goals[i].first.size() - 1)
        ostr << " , ";
    };
    ostr << " |-- ";
    ostr << goals[i].second << endl;
  };
  
  return ostr;
}