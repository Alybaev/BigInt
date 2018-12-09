
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "BigInt.h"
using namespace std;

BigInt subtract(BigInt& a, BigInt& b,bool& isNegative);
BigInt add(vector<int>& a, vector<int>& b,bool& isNegative);
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
	

	while (sinp.get(ch)){
		if (not isdigit(ch)) {
			throw runtime_error("BigInt: incorrect string initializer");
		}
		digits.push_back(ch - '0');
	}
	if(digits.size() > 1){
		eraseLeadingZeros();
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

	while(digits.size() != 1 and digits[0] == 0)
	{	
		digits.erase(digits.begin());
	}
	
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

BigInt operator-(BigInt& a, BigInt& b){
	
	bool isNegative = false;
	if(a.isNegative and b.isNegative){
		b.isNegative = false;
		a.isNegative = false;
		return b - a;
	}else if(a.isNegative and !b.isNegative){
		b.isNegative = true;
		return a + b;
	}else if(!a.isNegative and b.isNegative){
		b.isNegative = false;
		return b + a;
	}
	
	if(abs(a) < abs(b)){
		isNegative = true;
		vector<int> t;
		t = a.digits;
		a.digits = b.digits;
		b.digits = t;
	}
	
	return subtract(a,b,isNegative);
	
	
}
BigInt subtract(BigInt& a, BigInt& b,bool& isNegative){
	string res = "";
	BigInt c;
	int diffSize = a.size() - b.size();
	for(int i = a.size() - 1,j = b.size() - 1; i >= diffSize;i--,j--){
		if(a.digits[i] - b.digits[j] < 0){
			a.digits[i] += 10;
			int k = i;
			while(a.digits[k - 1] == 0){
				a.digits[k - 1] = 9;
				k--;
			}
			a.digits[k - 1]--;
		}
		int sub = a.digits[i] - b.digits[j];
		res = to_string(sub) + res;
	}
	for(int i = diffSize-1;i >= 0;i--){
		res = to_string(a.digits[i]) + res;
	}
	c = BigInt(res);
	c.isNegative = isNegative;
	return c;
}
BigInt operator+(BigInt& a, BigInt& b){
	bool isNegative;
	
	if(a.isNegative && !b.isNegative){
		a.isNegative = false;
		return b - a;
	}else if(b.isNegative && !a.isNegative){
		b.isNegative = false;
		return a - b;
	}else if(b.isNegative && a.isNegative){
		isNegative = true;
	}
	vector<int> bigMax = a.digits;
	vector<int> bigMin = b.digits;
	
	long long maxSize = max(a.size(),b.size());
	long long minSize = min(a.size(),b.size());
	
	
	if(b.size() == maxSize){
		bigMax = b.digits;
		bigMin = a.digits;
	}
	
	
	return add(bigMax,bigMin,isNegative);
	
}
BigInt add(vector<int>& bigMax, vector<int>& bigMin,bool& isNegative){
	long long diffInSize = bigMax.size() -  bigMin.size();
	string res = "";
	int i = bigMax.size() - 1;
	int j = bigMin.size();
	if(bigMax.size() !=  bigMin.size()){
		bigMin.insert(bigMin.begin(),0);
	}else{
		j = bigMin.size() - 1;
		diffInSize++;
	}
	bool carry = false;
	int sum = 0;
	
	
	while(i >= diffInSize - 1){
		
		
		sum = bigMax[i] + bigMin[j];
	
		if(carry){
			++sum;
		}
		if(sum >= 10){
			res = to_string(sum % 10) + res;
			carry = true;
		}else{
			res = to_string(sum) + res;
			carry = false;
		}
		i--;
		j--;
		
	}
	if(carry && bigMax.size() == bigMin.size()){
		res =  "1" +  res;
	}else{
		for(int i = diffInSize - 2;i >= 0;i--){
			
			res =  to_string(bigMax[i])+  res;
			
		}
	}
	BigInt c = BigInt(res);
	c.isNegative = isNegative;
	return c;
	
	
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






