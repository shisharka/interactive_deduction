#include <sstream>
// #include <map>
// #include <vector>
// #include <set>
// #include <memory>
// #include <algorithm>
// #include <functional>
// #include <stdio.h>
// #include <stdlib.h>
#include "formula.hpp"

// Function for printing formula to an output stream
ostream & operator << (ostream & ostr, const Formula & f) {
  f->printFormula(ostr);
  return ostr;
}

// ------------------------ constructors --------------------------
Atom::Atom(const Variable & v) : _v(v) {}

UnaryConnective::UnaryConnective(const Formula & op) 
  : _op(op) {}

BinaryConnective::BinaryConnective(const Formula & op1, const Formula & op2) 
  : _op1(op1), _op2(op2) {}
// ----------------------------------------------------------------

// --------------------------- getters ----------------------------
const Variable & Atom::getVariable() const {
  return _v;
}

const Formula & UnaryConnective::getOperand() const {
  return _op;
}

const Formula & BinaryConnective::getOperand1() const {
  return _op1;
}

const Formula & BinaryConnective::getOperand2() const {
  return _op2;
}
// ----------------------------------------------------------------

// --------------------------- getType ----------------------------
FormulaType True::getType() const {
  return T_TRUE;
}

FormulaType False::getType() const {
  return T_FALSE;
}

FormulaType Atom::getType() const {
  return T_ATOM;
}

FormulaType Not::getType() const {
  return T_NOT;
}

FormulaType And::getType() const {
  return T_AND;
}

FormulaType Or::getType() const {
  return T_OR;
}

FormulaType Imp::getType() const {
  return T_IMP;
}

FormulaType Iff::getType() const {
  return T_IFF;
}
// ----------------------------------------------------------------

// ------------------------- printFormula -------------------------
void True::printFormula(ostream & ostr) const {
  ostr << "True";
}

void False::printFormula(ostream & ostr) const {
  ostr << "False";
}

void Atom::printFormula(ostream & ostr) const {
  ostr << _v;
}

void Not::printFormula(ostream & ostr) const {
  ostr << "~" << _op;
}

void And::printFormula(ostream & ostr) const {
  ostr << "(" << _op1 << " /\\ " << _op2 << ")";
}

void Or::printFormula(ostream & ostr) const {
  ostr << "(" << _op1 << " \\/ " << _op2 << ")";
}

void Imp::printFormula(ostream & ostr) const {
  ostr << "(" << _op1 << " => " << _op2 << ")";
}

void Iff::printFormula(ostream & ostr) const {
  ostr << "(" << _op1 << " <=> " << _op2 << ")";
}
// ----------------------------------------------------------------

// --------------------------- equalTo ----------------------------
bool LogicConstant::equalTo(const Formula & f) const {
  return f->getType() == getType();
}

bool Atom::equalTo(const Formula & f) const {
  if(f->getType() != T_ATOM)
    return false;

  Atom * a = (Atom *) f.get();
  
  return a->getVariable() == _v;
}

bool UnaryConnective::equalTo(const Formula & f) const {
  if(f->getType() != getType())
    return false;

  UnaryConnective * uc = (UnaryConnective *) f.get();
  
  return uc->getOperand()->equalTo(_op);
}

bool BinaryConnective::equalTo(const Formula & f) const {
  if(f->getType() != getType())
    return false;

  BinaryConnective * bc = (BinaryConnective *) f.get();
  
  return bc->getOperand1()->equalTo(_op1) &&
          bc->getOperand2()->equalTo(_op2);
}
// ----------------------------------------------------------------

// -------------------------- simplify ----------------------------
Formula BaseFormula::simplify() {
  return shared_from_this();
}

Formula Iff::simplify() {
  return make_shared<And>(make_shared<Imp>(_op1, _op2),
                          make_shared<Imp>(_op2, _op1));
}
// ----------------------------------------------------------------
