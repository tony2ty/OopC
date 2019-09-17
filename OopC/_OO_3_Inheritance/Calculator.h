
#ifndef CALCULATOR_H__
#define CALCULATOR_H__

#include <OopBase.h>

CLASSDEF(Calculator)

typedef struct { double dblOpL; double dblOpR; } Calculator_Input;
typedef ParamNull Calculator_Add;
typedef struct { double *pdblRet; } Calculator_Output;
typedef struct { double dblOpL; double dblOpR; double *pdblRet; } Calculator_Subtract;
typedef struct { double dblOpL; double dblOpR; double* pdblRet; } Calculator_Multiply;

#endif // !CALCULATOR_H__
