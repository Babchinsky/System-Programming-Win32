#pragma comment(lib, "DllFor16HW")
#pragma once
#include <iostream>
using namespace std;

#include "../DllFor16HW/DllFor16HW.h"

int main()
{
	cout << Sum(3,2) << endl;
	cout << Difference(3,2) << endl;
	cout << Product(3,2) << endl;
	cout << Quotient(3,2) << endl;
	return 0;
}
