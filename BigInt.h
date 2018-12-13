#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <iosfwd>
#include <vector>
#include <string>


class BigInt {

	
	friend std::ostream& operator<<(std::ostream& out, const BigInt& x);
	friend std::istream& operator>>(std::istream& out, BigInt& x);
	friend bool operator==(const BigInt& a, const BigInt& b);
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator>(const BigInt& a, const BigInt& b);
	friend bool operator<(const BigInt& a, const BigInt& b);
	friend bool operator>=(const BigInt& a, const BigInt& b);
	friend bool operator<=(const BigInt& a, const BigInt& b);

	
	
	friend BigInt operator-=(const BigInt& a, const BigInt& b);
	friend BigInt operator+(const BigInt& a,const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt subtract(BigInt& a, BigInt& b,bool& isNegative);
	friend BigInt add(std::vector<int>& a, std::vector<int>& b,bool& isNegative);
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	
	friend BigInt operator-(BigInt& a){
		BigInt b = a;
		b.isNegative = not a.isNegative;
		return b;
	}
	
	friend BigInt& operator+(BigInt& a) {
		return a;
	}
	
	
	
	public:
	BigInt& operator+=(const BigInt& b){
		*this = *this + b;
		return *this;
	}
	BigInt& operator-=(const BigInt& b){
		*this = *this - b;
		return *this;
	}
	BigInt()
	:isNegative(false) {
		digits.push_back(0);
	}

	explicit BigInt(const std::string& s);
	
	const  BigInt operator++(int);
	const  BigInt operator--(int);
	BigInt& operator++();
	BigInt& operator--();
	friend BigInt abs(BigInt x){
		x.isNegative = false;
		return x;
	}
   
	BigInt(const int& x) 
	:isNegative(false) {
		std::string xStr = std::to_string(x);
		if(xStr[0] == '-'){
			isNegative = true;
			xStr = xStr.substr(1,xStr.size());
		}
		for(char& c : xStr){
			digits.push_back(c - '0');
		}
		
		
	}
	

	private:
		void eraseLeadingZeros();
	int size() const{
		return digits.size();
	}
	
	bool isNegative;
	std::vector<int> digits;

};











BigInt operator/=(const BigInt& a, const BigInt& b);
BigInt operator*=(const BigInt& a, const BigInt& b);

#endif