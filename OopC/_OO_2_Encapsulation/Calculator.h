
#ifndef CALCULATOR_H__
#define CALCULATOR_H__

#include <OopBase.h>

CLASSDEF(Calculator)

typedef struct { double dblOperandL; double dblOperandR; } Calculator_Input;
typedef ParamNull Calculator_Add;
typedef struct { double* pResult; } Calculator_Output;

#endif // !CALCULATOR_H__
