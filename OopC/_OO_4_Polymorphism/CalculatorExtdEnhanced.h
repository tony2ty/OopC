
#ifndef CALCULATOREXTDENHANCED_H__
#define CALCULATOREXTDENHANCED_H__

#include "CalculatorBase.h"

CLASSDEF(CalculatorExtdEnhanced)

typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdEnhanced_Add;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdEnhanced_Subtract;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdEnhanced_Multiply;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdEnhanced_Divide;

#endif // !CALCULATOREXTENHANCED_H__
