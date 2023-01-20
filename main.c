#include "lib/include.h"
//main.c -> Aqui solo llamo a la función

//Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros.
 *
 */
int main(void)
{

    Configurar_PLL();           // Confiuracion de velocidad de reloj
    Configura_Reg_PWM0(8);      // Configuro a 10khz el pwm (lo mando llamar)
   
    while(1)
    {
        
    }

}
