
#ifndef CALCULATORBASE_H__
#define CALCULATORBASE_H__

#include <OopBase.h>

CLASSDEF(CalculatorBase)

typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorBase_Add;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorBase_Subtract;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorBase_Multiply;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorBase_Divide;

#endif // !CALCULATORBASE_H__
