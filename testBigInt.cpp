#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "BigInt.h"

using namespace std;

TEST_CASE ("Check constructors", "[ctor]") {
	ostringstream sout;

	SECTION("BigInt()") {
		BigInt x;
		sout << x;
		REQUIRE(sout.str() == "0");

	}
	SECTION("BigInt(const int)") {
		SECTION("CASE 1") {
			BigInt x(123);
			sout << x;
			REQUIRE(sout.str() == "123");
		}
		
		
	}
	SECTION("BigInt(const string&)") {
		SECTION("CASE 1") {
			BigInt x("123");
			sout << x;
			REQUIRE(sout.str() == "123");
		}
		SECTION("CASE 2") {
			BigInt x("-123");
			sout << x;
			REQUIRE(sout.str() == "-123");
		}
		SECTION("CASE 3") {
			REQUIRE_THROWS_AS(BigInt("---123"), runtime_error);
			REQUIRE_THROWS_AS(BigInt("hello"), runtime_error);
			REQUIRE_THROWS_AS(BigInt("123 123"), runtime_error);

		}
	}


}
TEST_CASE ("Check istream", "[cin]") {

	 BigInt x;
	 ostringstream sout;
	SECTION("Read positive BigInt without spaces") {
		string inp = "10101";
		istringstream sinp(inp);
		sinp >> x;
         sout << x;
         REQUIRE(sout.str() == "10101");

	}
	SECTION("Read negative BigInt") {
		string inp = "-1234";
		istringstream sinp(inp);
        sinp >> x;
        sout << x;
          REQUIRE(sout.str() == "-1234");

	}
	SECTION("Read huge negative BigInt") {
		string inp = "-12341234123412341234";
		istringstream sinp(inp);
        sinp >> x;
        sout << x;
          REQUIRE(sout.str() == "-12341234123412341234");

	}
	SECTION("Read positive BigInt with spaces") {
		string inp = "1 2 3 4";
		istringstream sinp(inp);
		
          bool succ =  bool(sinp >> x);
		  
          REQUIRE_FALSE(succ);

	}
	SECTION("Read positive BigInt string") {
		string inp = "Dosya";
		istringstream sinp(inp);
		
          bool succ = bool(sinp >> x);
		  
          REQUIRE_FALSE(succ);

	}
}
TEST_CASE("check comparison","[comparison]")
{
	SECTION("check equality"){
		REQUIRE(BigInt(100) == BigInt(100));
		REQUIRE(BigInt() == BigInt());
		REQUIRE(BigInt(100) == BigInt("100"));
		REQUIRE(BigInt(-333) == BigInt("-333"));
		REQUIRE(BigInt("100000000000") == BigInt("100000000000"));
		REQUIRE_FALSE(BigInt(-1) == BigInt(1));
	}
	SECTION("check inequality"){
		REQUIRE(BigInt(100) != BigInt(101));
		REQUIRE(BigInt() != BigInt(1));
		REQUIRE(BigInt(101) != BigInt("100"));
		REQUIRE(BigInt("100000000000") != BigInt("110000000000"));
		REQUIRE(BigInt("-1") != BigInt(1));
		REQUIRE_FALSE(BigInt("-2") != BigInt(-2));
	}
	SECTION("check >"){
		REQUIRE(BigInt(101) > BigInt(100));
		REQUIRE(BigInt(1) > BigInt());
		REQUIRE(BigInt(101) > BigInt("100"));
		REQUIRE(BigInt(101) > BigInt("-100"));
		REQUIRE(BigInt() > BigInt(-101));
		REQUIRE(BigInt(-100) > BigInt(-101));
		REQUIRE(BigInt("-100") > BigInt("-101"));
		REQUIRE_FALSE(BigInt(-100) > BigInt(-100));
		REQUIRE_FALSE(BigInt(101) > BigInt("101"));
		REQUIRE_FALSE(BigInt("100000000000") > BigInt("110000000000"));
	}
	SECTION("check <="){
		REQUIRE(BigInt(100) <= BigInt(101));
		REQUIRE(BigInt("100") <= BigInt(100));
		REQUIRE(BigInt() <= BigInt());
		REQUIRE(BigInt("999") <= BigInt(1000));
		REQUIRE(BigInt("12345678910") <= BigInt("12345678910"));
		REQUIRE(BigInt(-100) <= BigInt(-100));
		REQUIRE(BigInt("-101") <= BigInt("-100"));
		REQUIRE_FALSE(BigInt(101) <= BigInt("100"));
	}
	SECTION("check <"){
		REQUIRE(BigInt("-101") < BigInt("-100"));
		REQUIRE_FALSE(BigInt(-100) < BigInt(-100));
		REQUIRE(BigInt(100) < BigInt(101));
		REQUIRE(BigInt(-100) < BigInt(-99));
		REQUIRE(BigInt() < BigInt(1));
		REQUIRE(BigInt("999") < BigInt(1000));
		REQUIRE(BigInt("12345678910") < BigInt("12345678911"));
		REQUIRE_FALSE(BigInt(-100) < BigInt(-100));
		REQUIRE_FALSE(BigInt(101) < BigInt("100"));
		REQUIRE_FALSE(BigInt("100") < BigInt(100));
	}
	SECTION("check >="){
		REQUIRE(BigInt(102) >= BigInt(101));
		REQUIRE(BigInt("100") >= BigInt(100));
		REQUIRE(BigInt() >= BigInt());
		REQUIRE(1000 >= BigInt("999"));
		REQUIRE(BigInt("12345678910") >= BigInt("12345678910"));
		REQUIRE(BigInt(-100) >= BigInt(-100));
		REQUIRE(BigInt("-100") >= BigInt("-101"));
		REQUIRE_FALSE(BigInt(100) >= BigInt("101"));
	}
		
}

TEST_CASE("Unary operators" ,"[unary]"){
	
	ostringstream sout;
	BigInt x;
	SECTION("+ unary with constructor(int)"){
		x = BigInt(2);
		sout << +x;
		REQUIRE(sout.str() == "2");
	}
	SECTION("+ unary with constructor(string)"){
		x = BigInt("100000000000000000");
		sout << +x;
		REQUIRE(sout.str() == "100000000000000000");
	}
	SECTION("- unary with constructor(int)"){
		x = BigInt(2);
		sout << -x;
		REQUIRE(sout.str() == "-2");
	}
	SECTION("- unary with constructor(string)"){
		x = BigInt("100000000000000000");
		sout << -x;
		REQUIRE(sout.str() == "-100000000000000000");
	}
	
	
}
TEST_CASE("prefix" ,"[prefix]"){
	
	ostringstream sout;
	BigInt x;
	SECTION("addition"){
		SECTION("Case 1"){
			x = BigInt(999);
			
			REQUIRE(++x == 1000);
		}
		SECTION("Case 2"){
			x = BigInt("99");
			
			REQUIRE(++x == 100);
			REQUIRE(++x == 101);
			REQUIRE(x++ == 101);
			REQUIRE(x == 102);
		}
		SECTION("Case 3"){
			x = BigInt(-1);
			REQUIRE(++x == BigInt());
			REQUIRE(++x == 1);
			REQUIRE(x++ == 1);
			REQUIRE(-x == -2);
		}
		
		
		
		
	}
	SECTION("subtraction"){
		SECTION("Case 1"){
			x = BigInt(1000);
		
			REQUIRE(--x == 999);
			REQUIRE(--x == 998);
			REQUIRE(x-- == 998);
			REQUIRE(x == 997);
		}
		SECTION("Case 2"){
			x = BigInt(1);
			REQUIRE(--x == BigInt());
			REQUIRE(--x == -1);
			REQUIRE(x-- == -1);
			REQUIRE(-x == 2);
		}
		
		
		
	}
	
	
	
}
TEST_CASE("postfix" ,"[postfix]"){
	
	ostringstream sout;
	BigInt x;
	SECTION("addition"){
		SECTION("Case 1"){
			x = BigInt(999);
			sout << x++;
			REQUIRE(sout.str() == "999");
		}
		
		
		
	}
	SECTION("subtraction"){
		SECTION("Case 1"){
			x = BigInt(1000);
			sout << x--;
			REQUIRE(sout.str() == "1000");
		}
		
		
		
	}
	
	
	
}

TEST_CASE("Arithmetic Operations","[arithmetic]"){
	BigInt a,b,c;
	ostringstream sout;
	SECTION("Addition"){
		SECTION("Case 1"){
			a = BigInt(2200);
			b = BigInt(20);
			c = BigInt(2220);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 2"){
			a = BigInt(256);
			b = BigInt(256);
			c = BigInt(512);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 3"){
			a = BigInt(1);
			b = BigInt("256");
			c = BigInt(257);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 4"){
			a = BigInt(1);
			b = BigInt("9");
			c = BigInt(10);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		
		SECTION("Case 5"){
		
			REQUIRE(BigInt(1) + BigInt("9") == BigInt(10));
		}
		SECTION("Case 6"){
			a = BigInt("10000000000000000000000009");
			b = BigInt("10000000000000000000000009");
			c = BigInt("20000000000000000000000018");
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 7"){
			a = BigInt(999);
			b = BigInt("999");
			c = BigInt(1998);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 8"){
			a = BigInt(3392);
			b = BigInt("38");
			c = BigInt(3430);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 9"){
			a = BigInt(15555);
			b = BigInt(5555);
			c = BigInt(21110);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 10"){
			a = BigInt(222);
			b = BigInt(222);
			c = BigInt(444);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 11"){
			a = BigInt(1);
			b = BigInt(1);
			c = BigInt(2);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 12"){
			a = BigInt(11111);
			b = BigInt(22);
			c = BigInt(11133);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 13"){
			a = BigInt();
			b = BigInt();
			c = BigInt();
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 14"){
			a = BigInt(15);
			b = BigInt(-20);
			c = BigInt(-5);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 14"){
			a = BigInt("-55");
			b = BigInt(100);
			c = BigInt(45);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 15"){
			a = BigInt("-55");
			b = BigInt("-100");
			c = BigInt(-155);
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 16"){
			a = BigInt("100");
			b = BigInt("-100");
			c = BigInt();
			sout << a + b;
			REQUIRE(a + b == c);
		}
		SECTION("Case 17"){
			a = BigInt("199");
			b = BigInt("1");
			c = BigInt("200");
			sout << a + b;
			REQUIRE(a + b == c);
		}
	}
	SECTION("subtraction"){
		SECTION("Case 1"){
			a = BigInt(5);
			b = BigInt(1);
			c = BigInt(4);
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 2"){
			a = BigInt("12");
			b = BigInt(3);
			c = BigInt(9);
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 3"){
			a = BigInt("23");
			b = BigInt(122);
			c = BigInt(-99);
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 4"){
			a = BigInt("23");
			b = BigInt(23);
			c = BigInt(0);
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 5"){
			a = BigInt("1000");
			b = BigInt(1);
			c = BigInt(999);
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 6"){
			a = BigInt("1000");
			b = BigInt(1000);
			c = BigInt();
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 7"){
			a = BigInt("8888888888888888888888");
			b = BigInt("4444444444444444944144");
			c = BigInt("4444444444444443944744");
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 8"){
			a = BigInt("-3");
			b = BigInt("-6");
			c = BigInt("3");
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 9"){
			a = BigInt("1000");
			b = BigInt("-999");
			c = BigInt("1999");
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 10"){
			a = BigInt("-1000");
			b = BigInt("-999");
			c = BigInt("-1");
			sout << a - b;
			REQUIRE(a - b == c);
		}
		SECTION("Case 11"){
			a = BigInt("-1001");
			b = BigInt("3002");
			c = BigInt("-4003");
			sout << a - b;
			REQUIRE(a - b == c);
		}
	}
	
	
}

