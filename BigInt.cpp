
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include "BigInt.h"
using namespace std;

 BigInt::BigInt(const string& s)
	:isNegative(false) 
	{
	
	istringstream sinp(s);
	char ch;
	sinp >> ch;
	
	if (ch == '-' or ch == '+'){
		isNegative = ch == '-';
	} else if (isdigit(ch)) {
		digits.push_back(ch - '0');
	} else {
		throw runtime_error("BigInt: incorrect string initializer");
	}
	eraseLeadingZeros();

	while (sinp.get(ch)){
		if (not isdigit(ch)) {
			throw runtime_error("BigInt: incorrect string initializer");
		}
		digits.push_back(ch - '0');
	}
}

//cin and cout
ostream& operator<<(ostream& out, const BigInt& x){
	if (x.isNegative){
		out << '-';
	} 
	for (int d: x.digits){
		out << d;
	}
	return out;
}
void BigInt::eraseLeadingZeros(){
	int i = 0;
	while(i < digits.size() and digits[i] == 0)
	{
		i++;
	}
	digits.erase(digits.begin(), digits.begin() + i);
}

istream& operator>>(istream& inp, BigInt& x){
	char ch;
	string digits;
	bool isNegativeT;
	if (inp >> ch){
		if (ch == '-'){
			isNegativeT = true;
			
		}else{
			inp.unget();
		}
	} 
	
	while (inp.get(ch)){
		if(!isdigit(ch)){
			inp.setstate(ios_base::failbit);
			return inp;
		}
		digits += ch;
	}
	x = BigInt(digits);
	x.isNegative = isNegativeT;

	return inp;
}

//prefix
BigInt operator++(BigInt& a){
	if(a.isNegative){
		
		a.isNegative = false;
		--a;
		if(a.size() != 1 || a.digits[0] != 0){
			a.isNegative = true;
		}
		return a;
	}
	if(a.digits[a.size() - 1] == 9){
		if(equal(a.digits.begin() + 1, a.digits.end(), a.digits.begin())){
			a.digits.insert(a.digits.begin(), 0);
		}
		int i = a.size() - 1;
		while(a.digits[i] == 9){
			a.digits[i] = 0;
			i--;
		}
		++a.digits[i];
		
		return a;
		
	}
	++a.digits[a.size() - 1];
	return a;
	
	
}
BigInt operator--(BigInt& a){
	if((a.isNegative)or(a.size() == 1 && a.digits[0] == 0)){
		a.isNegative = false;
		++a;
		a.isNegative = true;
		return a;
	}
	if(a.digits[a.size() - 1] == 0){
		
		if(a.size() != 1 && a.digits.front() == 1){
			
			a.digits.erase(a.digits.begin());
			if(equal(a.digits.begin() + 1, a.digits.end(), a.digits.begin()) && a.digits.front() == 0){
				return BigInt(string(a.digits.size(),'9'));
			}
			a.digits.insert(a.digits.begin(),1);
					
		}	
		int i = a.size() - 1;
		while(a.digits[i] == 0){
			a.digits[i] = 9;
			i--;
		}
		--a.digits[i];
		return a;
		
	}
	
	--a.digits[a.size() - 1];
	return a;
	
	
}
// comparison operators
bool operator==(const BigInt& a, const BigInt& b){
	if((a.isNegative and b.isNegative) or (!(a.isNegative) and !(b.isNegative))){
		return (a.digits == b.digits);
	}
	return false;
}
bool operator!=(const BigInt& a, const BigInt& b){
	return not(a == b);
}

bool operator>(const BigInt& a, const BigInt& b){

	
	if(!a.isNegative and b.isNegative){
		return true;
	}
	if(a.isNegative and !b.isNegative){
		return false;
	}
	if((!a.isNegative and !b.isNegative) && (a.size() > b.size())){
		return true;
	}
	if((a.isNegative and b.isNegative) && (a.size() < b.size())){
		return true;
	}
	
	
	
	if(a.size() == b.size()){
		
		for(int i = 0;i < a.size();i++){
			
			if(a.digits[i] != b.digits[i]){
				
				if(a.isNegative and b.isNegative){
					return a.digits[i] < b.digits[i];
				}else{
					return a.digits[i] > b.digits[i];
				}
			}
			
		}
		
	}
	return false;
}
	
bool operator<=(const BigInt& a, const BigInt& b){
	return not(a > b);
}
bool operator<(const BigInt& a, const BigInt& b){
	return (not(a > b) and (a != b));
}
bool operator>=(const BigInt& a, const BigInt& b){
	return not(a < b);
}






