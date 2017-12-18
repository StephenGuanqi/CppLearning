//
// Created by Guanqi Yu on 12/8/17.
//

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int main() {

	unsigned cnt = 10;
	string bad[cnt]; // wrong, cnt not const expression
	constexpr unsigned sz = 42;
	string ints[sz];

	// element of array should be object, can't have reference array
	int a5[5] = {0,1,2}; // {0,1,2,0,0}
	string a3[3] = {"a", "b"}; // {"a", "b", ""}

	char a4[] = "c++";
//	char a6[6] = "Daniel";// wrong, no place for '\0'

	int a[] = {1, 2, 3};
//	int a2[] = a;       // array can't copy initialization
//	a3 = a;             // array is not assignable

	int arry[10];       // arry is default initialized
	fill_n(arry, 10, -1); // or arry = {0} , all initialized to 0; arry = {-1} only 1st elem is -1, rest are 0
	cout << "array[0] : " << arry[0] << endl;

	int (*parray)[10] = &arry;  // a pointer to 10 elem array
	int (&arrayref)[10] = arry; // a reference to 10 elem array

	/**
	 * Also use for-range loop to traverse all elems in the array
	 */
	int scores[10];         // must initialize
	for (auto i : scores)
		cout << i << " ";   // careful, this could cause undefined behaviour!

	int ia[] = {0, 1, 2, 3};
	auto ia2(&ia[0]);

	int *e = &arry[10]; // point to the next position of end elem
	for (int *b = arry; b != e; b++) ; // easy to erro, official below:
	/**
	 * loop : for-range; container/array -> iterator/pointer; subscript, not all supported
	 */
	int *begp = begin(arry);
	int *endp = end(arry);      // don't use end identifier!! it's an internal function
	while (begp != endp && *begp > 0)
		begp++;

	/** Only compare the value of two pointers when they both point to the same object **/


	/** STD library subscript must be an unsigned type, like string::size_type, no matter how long 32 or 64 or what
	 *  But the built-in subscript for an array can be signed, can dispose negative. Use size_t for unsigned subscript
	 * **/
	int *p = &arry[2];
	int k = p[-2]; // arry[0]
	cout << k << endl;

	/**
	 * C++ support cstring, but suggest not use them because it could be buffer flow error, which is unsafe
	 * C++ string is safer and more efficient than cstring opertions
	 */
	// C++
	string s1 = "a";
	string s2 = "b";
	string s3 = s1 + " " + s2;
	// C
	const char ch1[] = "Hello,";
	const char ch2[] = "World!";
	const size_t newsize = strlen(ch1) + strlen(" ") + strlen(ch2) + 1;
	char ch3[newsize];
	strcpy(ch3, ch1);
	strcat(ch3, " ");
	strcat(ch3, ch2);

	// C++ and C interface
	const char *str = s1.c_str();
	// if s1 change later, str may lose effect, best usage to recopy the char array to always use str

	// array size
	int int_array[] = {0, 1, 2, 3};
	cout << "size: " << sizeof(int_array) / sizeof(int_array[0]) << endl; // return 4

	// array can be used to initialize vector, copy initialize
	vector<int> ivec(begin(int_array), end(int_array));
	vector<int> ivec2(int_array + 1, int_array + 3);
	cout << ivec2.size() << endl; // 2

	/**
	 * Modern C++ should use vector & iterator rather than array & pointer
	 * use string rathern than cstring
	 */

	constexpr size_t rowCnt = 3, colCnt = 4;
	int iarry[rowCnt][colCnt];
	for (size_t i = 0 ; i != rowCnt; i++) {
		for (size_t j = 0; j != colCnt; j++)
			;
	}

	/**
	 * Important characteristics of array:
	 * when the array name is used, compiler automatically change it to pointer point to the first array
	 * **/
	p = arry; // same as p = &arry[0]
	// change value for double range loop
	cnt = 0;
	for (auto &row : iarry)
		for (auto &col : row) {
			col = cnt++;
		}
	// not change value
	for (auto &row : iarry) // outer loop still reference, prevent from array being changed to pointer
		for (auto col : row)
			cout << col << endl;
	/** row is not reference, changed to pointer **/
	for (auto row : iarry)
		for (auto col : row) // fatal error
			;
	/** When dealing with multi dimension array for-range, all auto are reference except for the innermost layer **/


	for (auto p = begin(iarry); p != end(iarry); p++)
		for (auto q = begin(*p); q != end(*p); q++)
			;

	/**
	 * loop : for-range; container/array -> iterator/pointer; subscript, not all supported
	 */
}