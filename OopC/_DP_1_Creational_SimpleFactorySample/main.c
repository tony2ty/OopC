
#include <stdlib.h>
#include "IChart.h"
#include "FactoryChart.h"

int main(int argc, char **argv)
{
    IChart *pChart = FactoryChart_GetByName("histogram");

    INVOKE(IChart)(pChart, "Display", NULL);

    DELETE(IChart)(&pChart);

    system("pause");

    return 0;
}