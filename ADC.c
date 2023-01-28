#include "lib/include.h"
//Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros.
 *
 */

// MODULO 0 ADC
// A1N0 PE3 canal 0
// A1N1 PE2 canal 1 
// A1N2 PE1 canal 2

// SS3 - 1
// SS2 - 4
// SS1 - 4
// SS0 - 8

extern void Configura_Reg_ADC0(void)
{
    // Pag 396 para inicializa modulo 0 adc RCGCADC
    SYSCTL->RCGCADC = (1<<0);   // en la tiva grande tenemos 2 modulos

    // Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(0<<3)|(0<<2)|(0<<1)|(1<<0);
    // |= significa que mantenga las configuraciones previas

    // Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE_AHB->DIR = (0<<1) | (0<<2) | (0<<3); //PE1 PE2 PE3

    // (GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE_AHB->AFSEL =  (1<<1) | (1<<2) | (1<<3);

    // (GPIODEN) pag.781 desabilita el modo digital
    GPIOE_AHB->DEN = (0<<1) | (0<<2) | (0<<3);

    // Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFFFF000F);

    // (GPIOAMSEL) pag.786 habilitar analogico
    GPIOE_AHB->AMSEL = (1<<1) | (1<<2) | (1<<3);


    ///////////////////// configuración ADC ///////////////////////
    // Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    // Vmax conversión 2millones/s

    ADC0->PC = (0<<2) | (0<<1) | (1<<0);        //001 = 250ksps --> 2millones/8=250k

    // Pag 1099 Este registro (ADCSSPRI) configura la PRIORIDAD de los secuenciadores
    ADC0->SSPRI = 0x3210;

    // Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (0<<3) | (0<<2) | (0<<1) | (0<<0);        // DESACTIVO

    // Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX = (0x0000);      // evento de procesador

    // Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX1 = 0x0210; 
    //ADC0->SSMUX1 = (2<<0) | (1<<0) | (0<<0); //en el secuenciador 1 se asignar el canal 0 1 y 2



    //pag 1130 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción

}

extern void ADC0_InSeq2(uint16_t *Result,uint16_t *duty)
{
    

}


