#pragma once

#ifndef MyDll_API
#define MyDll_API extern "C" __declspec(dllimport)
#endif

MyDll_API int Sum(int a, int b);
MyDll_API int Difference(int a, int b);
MyDll_API int Product(int a, int b);
MyDll_API double Quotient(int a, int b);