
#ifndef CALCULATOREXTDCOMMON_H__
#define CALCULATOREXTDCOMMON_H__

#include "CalculatorBase.h"

CLASSDEF(CalculatorExtdCommon)

typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdCommon_Add;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdCommon_Subtract;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdCommon_Multiply;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } CalculatorExtdCommon_Divide;

#endif // !CALCULATOREXTDCOMMON_H__
