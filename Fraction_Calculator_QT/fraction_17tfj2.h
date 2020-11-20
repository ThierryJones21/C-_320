#include <iostream>
#include <fstream>

#ifndef FRACTION17TFJ2
#define FRACTION17TFJ2

using namespace std;

class Fraction {
public:
	Fraction();//default
	Fraction(int);//single
	Fraction(int, int);//double

	int gcd(int, int);//greatest common denominator

	int numerator();
	int denominator();
	void setNum(int);
	void setDen(int);

	Fraction simplify(void);
	Fraction assign(void);

	Fraction operator+(Fraction f);//add
	Fraction operator-(Fraction f);//sub
	Fraction operator*(Fraction f);//mult
	Fraction operator/(Fraction f);//div
	Fraction operator-(const int i);//sub int
	Fraction operator+(const int i);//add int

	friend Fraction operator-(int i, Fraction f);
	friend Fraction operator+(int i, Fraction f);

	Fraction operator-(void);//negation
	Fraction operator++(void);//pre add
	Fraction operator++(int);//post add

	void setVal(int, int);

	Fraction operator+=(Fraction f);//add equals

	bool operator<(Fraction input);
	bool operator<=(Fraction input);
	bool operator==(Fraction input);
	bool operator!=(Fraction input);
	bool operator>=(Fraction input);
	bool operator>(Fraction input);

	friend bool operator<(int i,Fraction input);
	friend bool operator>(Fraction input, int i);
	friend bool operator!=(Fraction input, int i);

private:
	int num;
	int den;
};

ostream& operator<<(ostream& os, Fraction dt);//int to string
istream& operator>>(istream& in, Fraction& f);

class FractionException {
public:
	FractionException(const string&);
	string what() const;
private:
	string message;
};

#endif 