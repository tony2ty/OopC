
#ifndef CALCULATOREXT_H__
#define CALCULATOREXT_H__

#include <OopBase.h>

CLASSDEF(CalculatorExt)

typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExt_Add;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExt_Subtract;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExt_Multiply;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExt_Divide;

#endif // !CALCULATOREXT_H__
