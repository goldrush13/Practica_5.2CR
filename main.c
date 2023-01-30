#include "lib/include.h"

/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz , utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa 
 *
 */


int main(void)
{
    uint16_t Result[3];
    uint16_t duty[3];   // ciclo de trabajo ct

    Configurar_PLL();
    Configura_Reg_ADC0();
    Configura_Reg_PWM0();
    

    while(1)
    {
        ADC0_InSeq2(Result,duty);

        PWM0->_0_CMPB = duty[0];
        PWM0->_1_CMPA = duty[1];
        PWM0->_2_CMPA = duty[2];

    }
    
}
