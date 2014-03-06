
#include "AS5040.h"

#define AS_CS_INIT(as)     GPO_Init(as->CS)
#define AS_CLK_INIT(as)    GPO_Init(as->CLK)
#define AS_DO_INIT(as)     GPI_Init(as->DO)

#define AS_CS_EN(as)       GPIO_Clr(as->CS)
#define AS_CS_DIS(as)      GPIO_Set(as->CS)
#define AS_CLK_H(as)       GPIO_Set(as->CLK)
#define AS_CLK_L(as)       GPIO_Clr(as->CLK)
#define AS_DO(as)          GPIO_Get(as->DO)

void AS_Init(const AS5040* const as)
{
    AS_CS_INIT(as);
    AS_CLK_INIT(as);
    AS_DO_INIT(as);
    AS_CS_DIS(as);
}
uint32  AS_GetData(const AS5040* const as)
{
    uint8  i, data[10];
    uint32 weight, sum;

    AS_CLK_H(as);
    AS_CS_EN(as);
    Delay_Us(10);
    AS_CLK_L(as);
    Delay_Us(1);
    AS_CLK_H(as);
    Delay_Us(1);

    for (i = 0; i < 10; i++)
    {
        data[i] = AS_DO(as);
        AS_CLK_L(as);
        Delay_Us(1);
        AS_CLK_H(as);
        Delay_Us(1);
    }
    sum = 0; weight = 1;
    for (i = 0; i < 10; i++)
    {
        sum += data[9 - i] * weight; //(1<<i) ;
        weight *= 2;
    }
    AS_CLK_H(as);
    AS_CS_DIS(as);
    return sum;
}


