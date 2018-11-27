//
// Created by Alexander Dimopoulos on 11/25/18.
//
#include "complexNumber.h"
#include <math.h>
#define _USE_MATH_DEFINES

complexNumber::complexNumber()
{
    realNumber = 0;
    imaginaryNumber = 0;
}

complexNumber::~complexNumber()
{
    eraseAll();
}

complexNumber::complexNumber(const mixedNumber &a, const mixedNumber &b)
{
    setValue(a, b);
}

void setValue(const complexNumber &a, const complexNumber &b)
{
    setValue(a, b);
}


complexNumber& complexNumber::operator=(const complexNumber &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

mixedNumber complexNumber::getReal()
{
    return realNumber;
}

mixedNumber complexNumber::getImaginary()
{
    return imaginaryNumber;
}

complexNumber complexNumber::getConjugate()
{
    //create a complexNumber object newbie
    //check if there is a denominator
    //if yes, get its value and make sure the answer has a numerator and denominator
    //else take the sign for the imaginary number and flip it (ex. - => +)
    //return newbie

    mixedNumber imNew;
    complexNumber newbie;

    imNew= this->imaginaryNumber * -1;
    newbie.setValue(this->realNumber, imNew);

    return newbie;
}
// TODO
complexNumber complexNumber::pow(const complexNumber& base, const complexNumber& exponent)
{
    //figure out how to take a complex number to the power of another complex number
    complexNumber send;
    send = pow(base, exponent);
    return send;
}

mixedNumber complexNumber::getMagnitude() //find r
{
    //magnitute is found by taking the real number (p) and the imaginary number (q)
    //  squaring them, adding them together, then taking the square root
    //sqrt( p^2 + q^2)
//    mixedNumber p = getReal(), q = getImaginary();
//    p = p^2;
//    q = q^2;
//    p = p + q;
//    q = p * p;
  double realDouble = static_cast<double>(realNumber.getNum()) / realNumber.getDenom();
  double realDoubleSquared = realDouble * realDouble;
  double imaginaryDouble = static_cast<double>(imaginaryNumber.getNum()) / imaginaryNumber.getDenom();
  double imaginaryDoubleSquared = imaginaryDouble * imaginaryDouble;
  double magnitude = sqrt(realDoubleSquared + imaginaryDoubleSquared);
  mixedNumber result(magnitude);
  return result;
}

// TODO GET ALEXANDER'S CODE
mixedNumber complexNumber::getDirection() //find (theta)
{
    //if p > 0 use: (theta) = tan^-1(q/p)
    //if p < 0 use: (theta) = tan^-1(q/p) + pi

    mixedNumber result;
    result = realNumber / imaginaryNumber;
   // result = atan(result);

    if(realNumber < 0)
        result += M_PI;

    return result;
}

void complexNumber::getPolar()
{
    mixedNumber r = getMagnitude();
    mixedNumber theta = getDirection();
    std::cout<<"Polar Coordinates: ("<<r<<", "<<theta<<")"<<std::endl;
}

bool complexNumber::isOrthogonal(const complexNumber &other)
{
    fraction dotProduct = realNumber * other.imaginaryNumber + imaginaryNumber * other.realNumber;
    return dotProduct.getNum() == 0;
}

void complexNumber::setValue(const mixedNumber &a, const mixedNumber &b)
{
    realNumber = a;
    imaginaryNumber = b;
}

void complexNumber::eraseAll()
{
    realNumber = 0;
    imaginaryNumber = 0;
}

void complexNumber::copy(const complexNumber& other)
{
    this->imaginaryNumber = other.imaginaryNumber;
    this->realNumber = other.realNumber;
}

complexNumber& complexNumber::operator+=(const complexNumber& other)
{
    *this = *this + other;
    return *this;
}

complexNumber& complexNumber::operator-=(const complexNumber& other)
{
    *this = *this - other;
    return *this;
}

complexNumber& complexNumber::operator*=(const complexNumber& other)
{
    *this = *this * other;
    return *this;
}

complexNumber& complexNumber::operator/=(const complexNumber& other)
{
    *this = *this / other;
    return *this;
}
