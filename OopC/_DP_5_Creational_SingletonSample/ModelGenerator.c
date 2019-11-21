//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include "ModelGenerator.h"

#include <stdio.h>

//����ģʽ����ʶ�����Ƿ����ɵı���
static bool bHasBeenGenerated = false;
//����
static ModelGenerator *pSingleton = NULL;

struct ModelGenerator_Fld
{
    CHAINDECLARE;

};

/////////////////////////////////////////////////////////////////////////
//

static void GetModel(ParamIn *pParams)
{
    ModelGenerator *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    int *pIntRetAsModel = va_arg(vlArgs, int *);

    //Todo: 
    *pIntRetAsModel = 11;
    printf("Model generated.\n");
}

/////////////////////////////////////////////////////////////////////////
//

static void __CLEAR(ModelGenerator)(void *pParams)
{
    ModelGenerator *pSelf = pParams;

    //�������ٺ󣬱�û�е����ˣ�
    //��˱�ʶ������Ϊfalse
    bHasBeenGenerated = false;
    pSingleton = NULL;
}

static bool __CALL(ModelGenerator)(ModelGenerator *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(ModelGenerator)(ModelGenerator *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(ModelGenerator)(ModelGenerator *pSelf)
{
    DODEL(pSelf, Object);
}

ModelGenerator *__NEW(ModelGenerator)()
{
    //����ͨ�������жϣ�
    //�������ֲ������������͹��Ϊ
    //ͬʱ����һ���������ͱ����������ݾ�����
    //�������ܴ��ʱ����Ȼ���Ƽ���������
    if (bHasBeenGenerated)
    {
        return pSingleton;
    }
    bHasBeenGenerated = true;

    DONEW(pNew, ModelGenerator, Object, __CLEAR(ModelGenerator),
        METHOD(GetModel));

    pSingleton = pNew;

    return pNew;
}
