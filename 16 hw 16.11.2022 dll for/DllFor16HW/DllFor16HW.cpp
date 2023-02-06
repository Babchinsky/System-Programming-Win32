#define MyDll_API extern "C" __declspec(dllexport)

#include "DllFor16HW.h"

MyDll_API int Sum(int a, int b)
{
	return a + b;
}

MyDll_API int Difference(int a, int b)
{
	return a - b;
}

MyDll_API int Product(int a, int b)
{
	return a * b;
}

MyDll_API double Quotient(int a, int b)
{
	return a * 1.0 / b;
}
