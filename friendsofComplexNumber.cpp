//
// Created by Alexander Dimopoulos on 11/26/18.
//

#include "complexNumber.h"

complexNumber operator+(const complexNumber& a, const complexNumber& b)
{
    complexNumber result;
    result.realNumber = a.realNumber + b.realNumber;
    result.imaginaryNumber = a.imaginaryNumber + b.imaginaryNumber;
    return result;
}

complexNumber operator-(const complexNumber& a, const complexNumber& b)
{
    complexNumber result;
    result.realNumber = a.realNumber - b.realNumber;
    result.imaginaryNumber = a.imaginaryNumber - b.imaginaryNumber;
    return result;
}

complexNumber operator*(const complexNumber& a, const complexNumber& b)
{
    complexNumber result;
    result.realNumber = a.realNumber * b.realNumber;

    result.imaginaryNumber = a.realNumber * b.imaginaryNumber;
    result.imaginaryNumber += a.imaginaryNumber * b.realNumber;

    result.realNumber += a.imaginaryNumber * b.imaginaryNumber * -1;
    return result;
}

complexNumber operator/(const complexNumber& a, const complexNumber& b)
{
  // Division is computed by multiplying the numerator and denominator by the conjugate of the denominator,
  //  then by dividing, separately, the real and imaginary components by the resulting denominator
  //  By multiplying the denominator by its conjugate, its imaginary component is eliminated
  complexNumber conjugate = b.getConjugate();
  complexNumber numerator = a * conjugate;
  mixedNumber denominator = (b * conjugate).getReal();
  complexNumber result;
  result.realNumber = numerator.getReal() / denominator;
  result.imaginaryNumber = numerator.getImaginary() / denominator;
  return result;
}

// TODO GET ALEXANDER'S CODE
// TODO ACCOUNT FOR 2 + i, ie, i with no coeffecient
std::ostream& operator<<(std::ostream &out, const complexNumber &m)
{
    out << m.realNumber << " + " << m.imaginaryNumber << "i";
    return out;
}

//needs more work
std::istream& operator>>(std::istream &in, complexNumber &m)
{
  std::stringstream ss;
  std::string possibleComplexNumber;
  if(&in == &std::cin) {
    getline(in, possibleComplexNumber);
    ss<<possibleComplexNumber;
    ss>>m;
  }
  else {
    mixedNumber temp;
    char symbol;
    if(in >> temp) { // get first mixed number
      if(in.peek() == 'i') { // is only imaginary number
        m.imaginaryNumber = temp;
      } else {
        m.realNumber = temp;
        if(in >> symbol) { // got a new character
          std::cout << "Got new character..." << std::endl;
          std::cout << "Character: " << symbol << std::endl;
          if(symbol == '+' || symbol == '-') { // valid character
            std::cout << "New character valid..." << std::endl;
            streamUtilities::consumeWhitespace(in);
            if(streamUtilities::hasNextInt(in) && in >> temp && in.peek() == 'i') { // valid mixed number and i
              std::cout << "Got valid mixed number and next character is an i" << std::endl;
              if(symbol == '+') {
                m.imaginaryNumber = temp;
              } else {
                m.imaginaryNumber = temp * -1;
              }
              char iTrash;
              in >> iTrash;
            } else if(in.peek() == 'i') {
              if(symbol == '+') {
                m.imaginaryNumber.setValues(1, 0, 1);
              } else {
                m.imaginaryNumber.setValues(-1, 0, 1);
              }
              char iTrash;
              in >> iTrash;
            }
          }
        }
      }
      in.clear();
    }
  }
  return in;
}

bool operator==(const complexNumber& a, const complexNumber& b)
{
    return a.realNumber == b.realNumber && a.imaginaryNumber == b.imaginaryNumber;
}
