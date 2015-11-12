#include "serial.h"
#include "serial.c"
#include "lpc17xx_adc.h"
//#include "lpc17xx_types.h"



#define adcfunc 1
#define adcport 0
#define adcpin1 23
#define adcpin2 24

int main(void){

PINSEL_CFG_Type PinCfg;

serial_init();
pin_settings(PinCfg, adcfunc, 0, 0, adcport, adcpin1);
pin_settings(PinCfg, adcfunc, 0, 0, adcport, adcpin2);
ADC_Init((LPC_ADC_TypeDef *)LPC_ADC, 20);
ADC_ChannelCmd((LPC_ADC_TypeDef *)LPC_ADC, 0, ENABLE);
while(1){
while (ADC_ChannelGetStatus((LPC_ADC_TypeDef *)LPC_ADC, 0, 0)){
    continue;
}
uint16_t x;
x = ADC_ChannelGetData((LPC_ADC_TypeDef *)LPC_ADC, 0);
char port[32] = "";
sprintf(port, "%i", x);
write_usb_serial_blocking(port, 32);
write_usb_serial_blocking("\n\r", 2);
}
}
