#include "mixednumber.h"

mixedNumber::mixedNumber()
{
}

mixedNumber::~mixedNumber()
{
    nukeEveryone();
}

mixedNumber::mixedNumber(int w, int n, int d)
{
    setValues(w,n,d);
}


mixedNumber::mixedNumber(const double &other)
{
    setValue(other);
}

mixedNumber::mixedNumber(const mixedNumber &other)
{
    copy(other);
}

mixedNumber& mixedNumber::operator=(const mixedNumber &other)
{
    if(this != &other)
       copy(other);
    return *this;
}


mixedNumber& mixedNumber::operator=(const fraction &other)
{
    num = other.getNum();
    denom = other.getDenom();
    return *this;
}


mixedNumber& mixedNumber::operator=(const int &other)
{
    fraction temp(other);
    *this = temp;
    return *this;
}

mixedNumber& mixedNumber::operator=(const double &other)
{
    fraction temp(other);
    *this = temp;
    return *this;
}

void mixedNumber::getValues(int &w, int &n, int &d)
{
    w = num/denom;
    n = num%denom;
    d = denom;
}

void mixedNumber::setValues(int w, int n, int d)
{
    fraction::setValue(w*d + n, d);
}

void mixedNumber::copy(const mixedNumber &other)
{
    num = other.num;
    denom = other.denom;
}

void mixedNumber::nukeEveryone()
{
    num = 0;
    denom = 1;
}

 std::ostream& operator<<( std::ostream &out, const mixedNumber &m)
{
     int whole = m.num/m.denom, numerator = m.num % m.denom;
     if(numerator == 0)
         out<<whole;
     else
         if(whole == 0)
             out<<numerator<<"/"<<m.denom;
        else
             out<<whole<<" "<<abs(numerator)<<"/"<<m.denom;
     return out;
}

 std::istream& operator>>( std::istream &in, mixedNumber &m)
{
  std::stringstream ss;
  fraction firstHalf, secondHalf;
  if(in >> firstHalf) {
    std::cout << "found first half: " << firstHalf << std::endl;
    if(firstHalf.getDenom() == 1) {
      std::cout << "Demon is equal to 1, moving on..." << std::endl;
      std::cout << "Peek is space: " << static_cast<bool>(in.peek() == ' ') << std::endl;

      if(mixedNumber::hasNextInt(in)) {
        in >> secondHalf;
        std::cout << "Found second half: " << secondHalf << std::endl;

        if(firstHalf.getNum() > 0) {
          m.setValue(secondHalf.getNum(), secondHalf.getDenom());
        } else {
          m.setValue(secondHalf.getNum() * -1, secondHalf.getDenom());
        }
        m.num += firstHalf.getNum() * secondHalf.getDenom();
      } else {
        m.setValue(firstHalf.getNum());
      }
    } else {
      m.setValue(firstHalf.getNum(), firstHalf.getDenom());
    }
    in.clear();
  }
  return in;
}

bool mixedNumber::hasNextInt(std::istream &in) {
  while(in.good() && in.peek() == ' ') {
    in.ignore();
  }
  if(in.good()) {
    char nextChar = static_cast<char>(in.peek());
    if(nextChar >= '0' && nextChar <= '9') {
      return true;
    }
  }
  return false;
}
