#include <iostream>
#include <string>
#include <stdint.h>
#include <cmath>
#include<ctgmath>

enum Currency {
    USD, GBP, DKK, HKD, EUR
};

class Money {
public:
    Money(long cents, Currency curren = USD) :cents(cents), curren(curren) {}
    double get_money();
    double set_money();
    int d_t_c(double dollars);
    double c_t_d();
    double rounding(double dollars);
    bool operator+(const Money& rhs);
    double currency_check(Currency obj);
    double conversion_usd(Currency cur);
private:
    long int cents;
    Currency curren;
};

//------------------------------------------------------
//overload operators

bool Money::operator+(const Money& rhs) {
    //this takes thw two currencies, changes them both to dollars & then adds them together.
    //from there it is changed back to the original lvalue currency by dividing by the original change value
    double change{ currency_check(this->curren) };
    cents *= change;
    double change_rhs{ currency_check(rhs.curren) };
    double val{ rhs.cents * change_rhs };
    std::round(val);
    cents = (cents + val) / change;
    return cents;
}

//-------------------------------------------------------
//getter
double Money::get_money(){
    long double dollars{ c_t_d() };
    std::cout << '$' << dollars << std::endl;
    return dollars;
}
//setter
double Money::set_money(){
    double dollars;
    std::cout << "Please enter amount of dollars: $";
    std::cin >> dollars;
    std::cout << std::endl;
    dollars = rounding(dollars);
    cents = d_t_c(dollars);
    return 0;
}

//-------------------------------------------------------
//member functions

//dollars to cents
int Money::d_t_c(double dollars){
    long cents_v = dollars * 100;
    return cents_v;
}

//cents to dollars
double Money::c_t_d() {
    double dollars = (double) cents / 100 ;
    return dollars;
}

 double Money::rounding(double dollars) {

     dollars = std::ceil(dollars * 100.0) / 100.0;

    return dollars;
}

 double Money::currency_check(Currency obj) {
     double  exc_rate{ 1 };
     switch (obj) {
     case USD:
         //matching
         exc_rate = 1;
         
         break;
     case GBP:
         //0.83
         exc_rate = 0.83;
         
         break;
     case DKK:
         //7.14
         exc_rate = 7.14;
         break;
     case HKD:
         //7.85
         exc_rate = 7.85;
         break;
     case EUR:
         //0.96
         exc_rate = 0.96 ;
         break;
     default:
         throw "No currency recognised";
     }
     return exc_rate;
 }

 double Money::conversion_usd(Currency cur) {
     
     return 0;
 }

int main()
{
    Money Cream(12);
    Cream.get_money();
    Money More_cream(18, HKD);
    Cream + More_cream;
    Cream.get_money();
    Cream.set_money();
    Cream.get_money();
}

