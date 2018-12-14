
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

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
	
	BigInt operator++(int);
	BigInt operator--(int);
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

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
void fillWithZeros(vector<int>& vec,long long size);
BigInt add(vector<int>& bigMax, vector<int>& bigMin,bool& isNegative);
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
BigInt& BigInt::operator++(){
		
	 *this = *this + 1;
	 return *this;
 }
BigInt& BigInt::operator--(){
	
	 *this = *this - 1;
	 return *this;
 }
 BigInt BigInt::operator++(int){
	BigInt t = *this;
	
	*this = *this + 1;
	return t;
	
	
	
}
 BigInt BigInt::operator--(int){
	BigInt t = *this;
	*this = *this - 1;
	return t;
		
		
}
BigInt operator-(const BigInt& num1,const BigInt& num2){
	BigInt a = num1;
	BigInt b = num2;
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
	
	if(a < b){
		isNegative = true;
		vector<int> t;
		t = a.digits;
		a.digits = b.digits;
		b.digits = t;
	}
	
	return subtract(a,b,isNegative);
	
	
}
BigInt subtract(BigInt& a, BigInt& b,bool& isNegative) {
	string res = "";
	BigInt c = BigInt();
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
BigInt operator+(const BigInt& num1, const BigInt& num2){
	bool isNegative;
	BigInt a = num1;
	BigInt b = num2;	
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
BigInt add(vector<int>& bigMax, vector<int>& bigMin,bool& isNegative) {
	long long diffInSize = bigMax.size() -  bigMin.size();
	string res = "";
	reverse(bigMax.begin(),bigMax.end());
	reverse(bigMin.begin(),bigMin.end());
	fillWithZeros(bigMin,bigMax.size());
	bool carry = false;
	for(int i = 0; i < bigMax.size();i++){
		int sum = bigMax[i] + bigMin[i];
		if(carry){
			++sum;
		}
		if(sum >= 10){
			
			res = to_string(sum % 10) + res;
			carry = true;
		}else {
			res = to_string(sum) + res;
			carry = false;
		}
	}
	if(carry){
		res = "1" + res;
	}
	BigInt c = BigInt(res);
	c.isNegative = isNegative;
	return c;
	
	
}
void fillWithZeros(vector<int>& vec,long long size){
	while(vec.size() != size){
		vec.push_back(0);
	}
	return ;
	
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









int main(){
	string inp; cin>>inp;
	string inp2; cin>>inp2;
	BigInt a(inp);
	BigInt b(inp2);
	cout << a + b;
	
	return 0;
}



