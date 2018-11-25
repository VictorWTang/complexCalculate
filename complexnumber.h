#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
#include <mixednumber.h>

class complexNumber
{
public:
  complexNumber();
  complexNumber(mixedNumber realPart, mixedNumber imaginaryPart);
  ~complexNumber();
  complexNumber(const complexNumber& other);
  complexNumber& operator=(const complexNumber& other);

  mixedNumber getReal();
  mixedNumber getImaginary();
  complexNumber getConjugate();
  void power(const complexNumber& raiseTo);
  mixedNumber getMagnitude();
  mixedNumber getDirection();
  bool isOrthogonalTo(const complexNumber& other);

  friend
  complexNumber operator+(const complexNumber& x, const complexNumber& y);

  friend
  complexNumber operator-(const complexNumber& x, const complexNumber& y);

  friend
  complexNumber operator*(const complexNumber& x, const complexNumber& y);

  friend
  complexNumber operator/(const complexNumber& x, const complexNumber& y);

  friend
  std::ostream& operator<<(std::ostream& out, const complexNumber& complex);

  friend
  std::istream& operator>>(std::istream& in, complexNumber& complex);

private:
  mixedNumber real, imaginary;
};

#endif // COMPLEXNUMBER_H
