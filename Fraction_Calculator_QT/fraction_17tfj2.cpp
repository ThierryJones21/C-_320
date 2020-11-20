#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "fraction_17tfj2.h"

using namespace std;

FractionException::FractionException(const string& m) : message(m) {}
string FractionException::what() const {
	return message;
}
//constructors
Fraction::Fraction() {//default no int
	this->num = 0;
	this->den = 1;
}
Fraction::Fraction(int a) {//single int
	this->num = a;
	this->den = 1;
}
Fraction::Fraction(int a, int b) {//double int
	this->num = a;
	this->den = b;
	if (den == 0) {
		throw FractionException("illegal denominator\n");
	}
	else {
		int result = gcd(num, den);
		this->num = this->num / result;
		this->den = this->den / result;
		assign();
	}
}
//setters getters
int Fraction::numerator(void) {
	return this->num;
}
int Fraction::denominator(void) {
	return this->den;
}
void Fraction::setNum(int Num) {
	this->num = Num;
}
void Fraction::setDen(int Den) {
	this->den = Den;
}
//Simplify fraction
Fraction Fraction::simplify(void) {
	int N = this->num;
	int D = this->den;
	int result = gcd(N, D);
	this->den = this->den / result;
	this->num = this->num / result;
	return *this;
}
//assign fraction pos or neg

Fraction Fraction::assign(void) {
	if (this->den == 0) {
		throw FractionException("illegal denominator.");
	}
	if (this->den < 0) {
		this->den *= -1;
		this->num *= -1;
	}
	return *this;
}
//Output stream
ostream& operator << (ostream& os, Fraction f) {
	os << f.numerator() << "/" << f.denominator() << endl;
	return os;
}

istream& operator >> (istream& in, Fraction& f) {
	string value;
	in >> value; //copy the input into a string to be parsed

	size_t found = value.find("/");

	if (found != string::npos) {
		int top = atoi(value.substr(0, found).c_str());;
		int bottom = atoi(value.substr(found + 1).c_str());
		if (top == 0 && bottom != 0) {
			f.setVal(0, 1);
		}
		else {
			f.setVal(top, bottom);
		}
	}
	else if (!value.empty()) {
		if (atoi(value.c_str()) == 0) {
			f.setVal(0, 1);
		}
		else {
			f.setVal(atoi(value.c_str()), 1);
		}
		return in;
	}
	
}
void Fraction::setVal(int n, int d) {
	this->num = n;
	this->den = d;
}
//Operators
//#######################################################################

Fraction Fraction::operator+(Fraction f) {//addition
	Fraction os;
	if (this->den == os.denominator()) {
		os.setDen(this->den);
		os.setNum(this->num + f.numerator());
	}
	else {
		os.setDen(this->den * f.denominator());
		os.setNum((this->num * f.denominator()) + (this->den * f.numerator()));
	}
	os.simplify();
	return os;
}
Fraction Fraction::operator-(Fraction f) {//subtraction
	Fraction os;
	if (this->den == os.denominator()) {
		os.setDen(this->den);
		os.setNum(this->num - f.numerator());
	}
	else {
		os.setDen(this->den * f.denominator());
		os.setNum((this->num * f.denominator()) - (this->den * f.numerator()));
	}
	os.simplify();
	return os;
}
Fraction Fraction::operator*(Fraction f) {//multiplication
	Fraction os;
	os.setDen(this->den * f.denominator());
	os.setNum(this->num * f.numerator());
	os.simplify();
	return os;
}
Fraction Fraction::operator/(Fraction f) {//division
	Fraction os;
	os.setDen(this->den * f.numerator());
	os.setNum(this->num * f.denominator());
	os.simplify();
	return os;
}
Fraction Fraction::operator-(int i) {//subtraction of an int
	Fraction os;
	os.setNum(this->num - (i * this->den));
	os.setDen(this->den);
	os.simplify();
	return os;
}
Fraction Fraction::operator-() {//negation
	this->num = this->num * -1;
	this->den = this->den;
	return *this;
}
Fraction Fraction::operator+(int i) {//addition of an int
	Fraction os;
	os.setNum(this->num + (i * this->den));
	os.setDen(this->den);
	os.simplify();
	return os;
}

Fraction Fraction::operator++(int) {//  ++ used as prefix	not done
	int temp = this->den;
	const Fraction old(*this);
	this->num = this->num + temp;
	return old;
}
Fraction Fraction::operator++() {// ++ used as postfix not done
	int temp = this->den;
	this->num = this->num + temp;
	return *this;
}
Fraction Fraction::operator+=(Fraction f) {//addition equals
	if (this->den == f.denominator()) {
		this->num = this->num + f.numerator();
	}
	else {
		this->num = ((this->num * f.denominator()) + (this->den * f.numerator()));
		this->den = (this->den * f.denominator());
	}
	simplify();
	return *this;
}
//Boolean operators
bool Fraction::operator<(Fraction f) {
	double a = this->num / this->den;
	double b = f.numerator() / f.denominator();
	if (a < b) {
		return true;
	}
	else
		return false;
}
bool Fraction::operator<=(Fraction f) {
	double a = this->num / this->den;
	double b = f.numerator() / f.denominator();
	if (a <= b) {
		return true;
	}
	else
		return false;
}
bool Fraction::operator==(Fraction input) {
	double a = this->num / this->den;
	double b = input.numerator() / input.denominator();
	if (a == b) {
		return true;
	}
	else
		return false;
}
bool Fraction::operator!=(Fraction f) {
	double a = this->num / this->den;
	double b = f.numerator() / f.denominator();
	if (a != b) {
		return true;
	}
	else
		return false;
}
bool Fraction::operator>=(Fraction f) {
	double a = this->num / this->den;
	double b = f.numerator() / f.denominator();
	if (a >= b) {
		return true;
	}
	else
		return false;
}
bool Fraction::operator>(Fraction f) {
	double a = this->num / this->den;
	double b = f.numerator() / f.denominator();
	if (a > b) {
		return true;
	}
	else
		return false;
}

//Friend operators for multiple variable overloads
Fraction operator-(int i, Fraction f) { //int - fraction
	Fraction os;
	os.setNum((i * f.denominator()) - f.numerator());
	os.setDen(f.denominator());
	os.simplify();
	return os;
}
Fraction operator+(int i, Fraction f) { //int - fraction
	Fraction os;
	os.setNum((i * f.denominator()) + f.numerator());
	os.setDen(f.denominator());
	os.simplify();
	return os;
}
bool operator>(Fraction f, int i) {//bool > int
	double a = i;
	double b = (f.numerator() / (double)f.denominator());
	if (a < b) {
		return true;
	}
	else
		return false;
}
bool operator<(int i, Fraction f) {//int < bool
	double a = i;
	double b = f.numerator() / (double)f.denominator();
	if (a < b) {
		return true;
	}
	else
		return false;

}
bool operator!=(Fraction f, int i) {// fraction != int
	double a = f.numerator() / (double)f.denominator();
	double b = i;
	if (a != b) {
		return true;
	}
	else
		return false;
}
//####################################################################
int Fraction::gcd(int a, int b) {//Euclydian algorithm to solve for gcd
	if (b != 0)
		return gcd(b, a % b);
	else
		return a;
}




