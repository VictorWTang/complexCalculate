#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "complexnumber.h"

class expression
{
public:
  expression();
  expression(char symbol, const complexNumber& complex);
  ~expression();
  expression(const expression& other);
  expression& operator=(const expression& other);

  expression getConjugate();
  void setSymbol(char symbol);
  char getSymbol() const;
  
  mixedNumber getMagnitude();
  mixedNumber getDirection();

  void raiseToPower(const complexNumber &power);

  friend
  expression operator+(const expression& x, const expression& y);

  friend
  expression operator-(const expression& x, const expression& y);

  friend
  expression operator*(const expression& x, const expression& y);

  friend
  expression operator/(const expression& x, const expression& y);

  friend
  std::ostream& operator<<(std::ostream& out, const expression& e);

  friend
  std::istream& operator>>(std::istream& in, expression& e);

private:
  char symbol;
  complexNumber complex;
};

#endif // EXPRESSION_H
