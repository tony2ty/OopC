
#include "FactoryChart.h"

#include "ChartHistogram.h"
#include "ChartLine.h"
#include "ChartPie.h"

#include <stdio.h>
#include <string.h>

IChart * FactoryChart_GetByName(char * pName)
{
    IChart *pRet = NULL;

    if (!strcmp(pName, "histogram"))
    {
        ChartHistogram *pHistogram = CREATE(ChartHistogram)();
        pRet = SWITCH(pHistogram, ChartHistogram, IChart);

        printf("��ʼ��������״ͼ��\n");
    }

    if (!strcmp(pName, "line"))
    {
        ChartLine *pLine = CREATE(ChartLine)();
        pRet = SWITCH(pLine, ChartLine, IChart);

        printf("��ʼ����������ͼ.\n");
    }

    if (!strcmp(pName, "pie"))
    {
        ChartPie *pPie = CREATE(ChartPie)();
        pRet = SWITCH(pPie, ChartPie, IChart);

        printf("��ʼ�����ñ�״ͼ.\n");
    }

    return pRet;
}
