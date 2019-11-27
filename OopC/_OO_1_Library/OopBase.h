
#ifndef OOPBASE_H__
#define OOPBASE_H__

#ifdef OOPBASE_API
#else
#define OOPBASE_API __declspec(dllimport)
#endif // OOPBASE_API


#include <stdbool.h>
#include <stdarg.h>


/*******************************************************/
/******************** Util Macros **********************/
/*******************************************************/

#define       __ABSTRACT                          \

#define       __OVERRIDE                          \

#define  __METHODDECLARE(dclr)                    \

#define          __CLASS                          \
						typedef struct __Template \

#define         __EXTEND                          \
						,                         \

#define            __NEW(theclass)                \
						New_ ## theclass()        \

#define    __CONSTRUCTOR(theclass)                \
						void* New_ ## theclass()  \

#define         __METHOD(mthd)                    \
						#mthd, mthd               \

#define        __METHODA(mthd)                    \
						#mthd, NULL               \

#define           __TYPE(theclass)                \
						#theclass                 \




/*******************************************************/
/***************** Basic APIs for OOP ******************/
/*******************************************************/

/*
 * class template.
 * Call will match method of subclass as possible,
 * while in some conditions, no method of subclass matched,
 * methods of super class will be tried to match in order,
 * of which super classes been inherited. */
struct __Template
{
	void* Fld;
	void* Ext;
	bool(*Call)(void* pSelf, const char* pMethodName, ...);
	void(*Destroy)(void* pSelf);
};

/*
 * pClassName: current class name
 * szFld:      size of data field of current class,
 *             if current class has no data field,
 *             szFld can be 0.
 * fnClear:    clear function of current class,
 *             if current class has no extra mem to free when destroy its inst,
 *             fnClear can be null.
 * szMthdNum:  method num of current class
 * szBaseNum:  number of super class inherited by current class
 * ...:        ["method1", method1, "method2", method2, New_superclass1, New_superclass2]
 *
 * example:
 * __New("SomeClass", New_SomeClass, sizeof(Fld_SomeClass), Clear, 3, 2,
 *       "method1", method1,
 *       *method2", method2,
 *       *method3", method3,
 *       New_SuperClass1,
 *       New_SuperClass2);
 *
 * note:
 * Inheriting directly from same two classes is not allowed.
 * class1 <-- class2, class3                                             right;
 * class1 <-- class2, class2                                             wrong;
 * class1 <-- class2, class3 and class2 <-- class4 and class3 <-- class4 right;
 * same method names are not allowed.
 * __New(... ...,
 *     "SAMEMETHOD", method1,
 *     "SAMEMETHOD", method2,
 *     ... ...,
 *	   New_SuperClass);     wrong;
 * __New(... ...,
 *     "method1", method1,
 *     "method2", method2,
 *     ... ...,
 *	   New_SuperClass);     write; */
OOPBASE_API void* __New(const char* pClassName, size_t szFld, void(*fnClear)(void*), size_t szMthdNum, size_t szBaseNum, ...);

/*
 * pSelf:      instance to convert
 * pClassName: type name to convert to
 *
 * Convert
 * from the exact type to direct inherited class, hence the indirect inherited class.
 * class   <-- super1,   super2,   super3
 *
 * super1  <-- super11,  super12,  super13,
 * super2  <-- super21,  super22,  super23,
 * super3  <-- super31,  super32,  super33,
 *
 * super11 <-- super111, super112, super113,
 * super12 <-- super121, super122, super123,
 * ...
 *
 * Given instance will be tried in the following order to convert to some type,
 * class    > super1   > super2   > super3  > super11 > super12 > super13 >
 * super21  > super22  > super23  > super31 > super32 > super33 >
 * super111 > super112 > super113 > ...
 *
 * In a word, conversion is processed by distance(inheritance level) and sequence(inheritance order).*/
OOPBASE_API void* __Cvt(void* pSelf, const char* pClassName);

/*
 * pSelf:       instance itself
 * pMethodName: method name of which to be called.
 *
 * Super
 * to match methods of super class by distance(inheritance level) and sequence(inheritance order),
 * and hence call the matched. */
OOPBASE_API bool  __Spr(void* pSelf, const char* pMethodName, ...);

#endif // !OOPBASE_H__
