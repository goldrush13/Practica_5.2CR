#include "lib/include.h"


int main(void)
{
    uint16_t Result[3];
    uint16_t ct[3];

    Configura_Reg_ADC0();
    Configura_Reg_PWM0(8);
    Configurar_PLL();
       

    while(1)
    {
        ADC0_InSeq2(Result,duty);

    }
    
}
