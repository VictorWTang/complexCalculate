#include "expression.h"

expression::expression()
{
}

expression::expression(char symbol, const complexNumber& complex) {
  this->complex = complex;
  this->symbol = symbol;
}

expression::~expression() {
  complex = complexNumber();
  symbol = 0;
}

expression& expression::operator=(const expression& other) {
  if(this != &other) {
    complex = other.complex;
  }
  return *this;
}

void expression::setSymbol(char symbol) {
  this->symbol = symbol;
}

char expression::getSymbol() const {
  return symbol;
}

expression expression::getConjugate() {
  expression exp;
  exp.complex = complex.getConjugate();
  return exp;
}

void expression::raiseToPower(const complexNumber& power) {
  complex.power(power);
}
