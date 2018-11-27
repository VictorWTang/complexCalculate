//
// Created by Alexander Dimopoulos on 11/25/18.
//#include "complexNumber.h"
#ifndef CS3ATEST2_COMPLEXNUMBER_H
#define CS3ATEST2_COMPLEXNUMBER_H

#include "mixednumber.h"


class complexNumber {
public:
    complexNumber();
    ~complexNumber();
    complexNumber(const mixedNumber &, const mixedNumber &);
    complexNumber& operator=(const complexNumber&);
    complexNumber& operator+=(const complexNumber&);
    complexNumber& operator-=(const complexNumber&);
    complexNumber& operator*=(const complexNumber&);
    complexNumber& operator/=(const complexNumber&);


    friend complexNumber operator+(const complexNumber&, const complexNumber&);
    friend complexNumber operator-(const complexNumber&, const complexNumber&);
    friend complexNumber operator*(const complexNumber&, const complexNumber&);
    friend complexNumber operator/(const complexNumber&, const complexNumber&);
    friend bool operator==(const complexNumber&, const complexNumber&);

    mixedNumber getReal();
    mixedNumber getImaginary();
    complexNumber getConjugate();
    static complexNumber pow(const complexNumber&, const complexNumber&);
    mixedNumber getMagnitude();
    mixedNumber getDirection();
    void getPolar();
    bool isOrthogonal(const complexNumber &);

    void setValue(const mixedNumber &, const mixedNumber &);

    friend
    std::ostream& operator<<(std::ostream &out, const complexNumber &m);

    friend
    std::istream& operator>>(std::istream &in, complexNumber &m);

protected:
    mixedNumber realNumber, imaginaryNumber;

private:
    void copy(const complexNumber &);
    void eraseAll();


};


#endif //CS3ATEST2_COMPLEXNUMBER_H
