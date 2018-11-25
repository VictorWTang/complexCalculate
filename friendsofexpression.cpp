#include "expression.h"

expression operator+(const expression& x, const expression& y) {
  expression e;
  e.complex = x.complex + y.complex;
  return e;
}

expression operator-(const expression& x, const expression& y) {
  expression e;
  e.complex = x.complex - y.complex;
  return e;
}

expression operator*(const expression& x, const expression& y) {
  expression e;
  e.complex = x.complex * y.complex;
  return e;
}

expression operator/(const expression& x, const expression& y) {
  expression e;
  e.complex = x.complex / y.complex;
  return e;
}

std::ostream& operator<<(std::ostream& out, const expression& e) {
  out << e.symbol << " = " << e.complex;
  return out;
}

std::istream& operator>>(std::istream& in, expression& e) {
  char equalsTrash;
  char tempChar;
  in >> tempChar;
  if(tempChar >= 'A' && tempChar <= 'Z') {
    e.symbol = tempChar;
    in >> equalsTrash;
  }
  in >> e.complex;
  return in;
}
