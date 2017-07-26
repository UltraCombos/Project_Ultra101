#include "ofMain.h"
#include "ofApp.h"
void print(float val)
{
	cout << val << "\t is " << typeid(val).name() << endl;
}
template<typename T>
void print2(T val)
{	
	cout << val << "\t is "<< typeid(val).name() << endl;
}
//========================================================================
int my_sizeof(int a[]) // array to pointer decay rule
{
	return sizeof(a);
}
template<int N>
int my_sizeof2(int (&a)[N])
{
	return sizeof(a);
}
//========================================================================
template<typename T>
class my_vec2
{
	T x;
	T y;
};
typedef my_vec2<float> my_vec2f;
using   my_vec2i = my_vec2<int>;
template<typename T>
void print_list(std::vector<T> & t_list)
{
	cout << "{ ";
	for (size_t i = 0; i != t_list.size(); ++i)
	{
		cout << t_list[i];
		if (i < t_list.size() -1 )
			cout << ", ";
	}
	cout << " }" << endl;
}

//========================================================================
int main() {	
	int val = 1234567890;
	print(val);
	print2(val);
	cout << "========================================================================" << endl;

	int a[] = { 5, 4, 3 };
	cout << "my_sizeof(a) = " << my_sizeof(a)<<endl;
	cout << "my_sizeof2(a) = " << my_sizeof2(a)<<endl;
	cout << "========================================================================" << endl;

	my_vec2f v2f;
	my_vec2i v2i;
	my_vec2<double> v2d;
	vector<int> int_list{1,2,3};
	cout << "int_list = ";
	print_list(int_list);

	vector<float> float_list{ 1,2,3 };
	cout << "float_list = ";
	print_list(float_list);
	
}
