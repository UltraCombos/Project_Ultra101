#include <iostream>
class my_int
{
public:
	my_int() {} //default constructor,it's created automatically if it doesn't exist.
	my_int(const int & v) // another constructor
		:val(v) //initializer list
	{}
private:
	int val = 0;
//////////////////////////////////////////////////////////////////////////

	// use friend because val is private
	// overload << for std::cout
	friend std::ostream& operator << (std::ostream& os, const my_int& my_integer)
	{
		os << my_integer.val;
		return os;
	}
	// overload + for "a + b"
	friend my_int operator + (const my_int& a, const my_int& b)
	{
		int r = a.val*b.val;
		return my_int(r);
	}
};
//========================================================================
int main( ){
	my_int a = 10;
	my_int b(20);
	my_int a_plus_b = a + b;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout <<  a << " + " << b << " = " << a_plus_b << std::endl;
}
