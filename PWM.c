// USANDO:  M0PWM4 - 49 - PG0(6) - GENERADOR 2
#include "lib/include.h"

extern void Configura_Reg_PWM0(uint16_t freq)
{
    // Habilito PWM0 pg 398 (la tiva grande solo tiene 1)
    SYSCTL->RCGCPWM |= (1<<0); 
    
    // Habilito el puerto G (porque usare el pin PG0) pg 383
    SYSCTL->RCGCGPIO |= (1<<6);
    
    // Habilito función alternativa para PG0 PG 770
    GPIOG_AHB->AFSEL |= (1<<0); // 0 por PG0 jeje

    // Habilito la salida de PG0
    GPIOG_AHB->DIR = (1<<0);

    // Combinación de pg 788 para ver que numero estan en el campo de bits (para PG0 es del 0 al 3)
    //                pg 1808 le tengo que poner un 6 porque ahí esta "M0PWM4"
    // Entonces pongo en el campo de bits 0, un 6
    GPIOG_AHB->PCTL |= (GPIOG_AHB->PCTL&0xFFFFFFF0) | 0x00000006;
    
    // El pin es digital:
    GPIOG_AHB->DEN |= (1<<0); 
    
    // PASO 5 Activo divisor 
    PWM0->CC &= ~(1<<20);  /*Enable o Disable Divisor  Pag 1747*/
    
    
    //////////////////// CONFIGURACION PARAMETROS PWM /////////////////
    
    // BLOQUEO (estoy usando generador 2)
    PWM0->_2_CTL = (0<<0);

    // Voy usar el comparador A
    /* Action for counter = 0 --> do nothing
       Action for counter = LOAD --> drive pwmA HIGH    */
    PWM0->_2_GENA = 0x0000008C;         //Registro de las acciones del pwm Pag 1722 (Pte 2, min 30)

    // Cargo el valor
    /*          cuentas = fclk/fpwm  
    para 1kHz:  cuentas = (16,000,000/1000)
    para 50kHz: cuentas = (20 000 000/50) = 400 000 cuentas */
    PWM0->_2_LOAD = 5000;

    // Establecer el valor del ciclo de trabajo
    PWM0->_2_CMPA = 3500;           // ciclo de trabajo 70%, los primeras 3500 cuentas estaran en alto, y despues va a bajar

    // DESBLOQUEO
    PWM0->_2_CTL = (1<<0);

    // Habilito el modulo para que me deje pasar la señal :D
    PWM0->ENABLE = (1<<4);          // pp 1687
}