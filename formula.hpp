#ifndef __FORMULA_HPP__
#define __FORMULA_HPP__ 1

#include <iostream>
#include <string>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <set>
#include <memory>
// #include <algorithm>
// #include <functional>
// #include <stdio.h>
// #include <stdlib.h>

using namespace std;

class BaseFormula; // abstract class for representation of formulas
typedef shared_ptr<BaseFormula> Formula; // data type for representation of formulas

// Formula types
enum FormulaType { T_TRUE, T_FALSE, T_ATOM, T_NOT, T_AND, T_OR, T_IMP, T_IFF };

// Variable data type
typedef string Variable;

class BaseFormula : public enable_shared_from_this<BaseFormula> {
public:
  virtual FormulaType getType() const = 0; // get formula type
  virtual void printFormula(ostream & ostr) const = 0; // print formula to an output stream 
  virtual bool equalTo(const Formula & f) const = 0; // check syntax equality of two formulas
  virtual Formula simplify(); // simplifying for equivalence
  virtual ~BaseFormula() {}
};

ostream & operator << (ostream & ostr, const Formula & f);

// Class for representation of logic constants (True, False)
class LogicConstant : public BaseFormula {
public:
  virtual bool equalTo(const Formula & f) const;
};

// Class for representation of True logic constant
class True : public LogicConstant {
public:
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of False logic constant
class False : public LogicConstant {
public:
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of atoms in propositional logic
class Atom : public BaseFormula {
private:
  Variable _v;
public:
  Atom(const Variable & v);
  const Variable & getVariable() const;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
  virtual bool equalTo(const Formula & f) const;
};

// Class for representation of unary connectives (includes Negation)
class UnaryConnective : public BaseFormula {
protected:
  Formula _op;
public:
  UnaryConnective(const Formula & op);
  const Formula & getOperand() const;
  virtual bool equalTo(const Formula & f) const;
};

// Class for representation of Negation formulas
class Not : public UnaryConnective {
public:
  using UnaryConnective::UnaryConnective;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of binary connectives
// (includes Conjunction, Disjunction, Implication, Equivalence)
class BinaryConnective : public BaseFormula {
protected:
  Formula _op1, _op2;
public:
  BinaryConnective(const Formula & op1, const Formula & op2);
  const Formula & getOperand1() const;
  const Formula & getOperand2() const;
  virtual bool equalTo(const Formula & f) const;
};

// Class for representation of Conjunction formulas
class And : public BinaryConnective {
public:
  using BinaryConnective::BinaryConnective;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of Disjunction formulas
class Or : public BinaryConnective {
public:
  using BinaryConnective::BinaryConnective;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of Implication formulas
class Imp : public BinaryConnective {
public:
  using BinaryConnective::BinaryConnective;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
};

// Class for representation of Equivalence formulas
class Iff : public BinaryConnective {
public:
  using BinaryConnective::BinaryConnective;
  virtual FormulaType getType() const;
  virtual void printFormula(ostream & ostr) const;
  // (A => B) /\ (B => A) instead of A <=> B
  virtual Formula simplify();
};

#endif
