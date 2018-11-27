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
    complexNumber result;
    result.realNumber = a.realNumber / b.realNumber;
    result.imaginaryNumber = a.imaginaryNumber / b.imaginaryNumber;
    return result;
}

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
            if(in >> temp && in.peek() == 'i') { // valid mixed number and i
              std::cout << "Got valid mixed number and next character is an i" << std::endl;
              if(symbol == '+') {
                m.imaginaryNumber = temp;
              } else {
                m.imaginaryNumber = temp * -1;
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
