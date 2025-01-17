/*
 * MC2.c
 */ 

#include "uart.h"
#include <string.h>
#include "i2c.h"
#include "external_eeprom.h"
int main(void)
{
	uint16 bot;
	uint8 key[9];
	UART_init();
	DDRB=0x0F;
	DDRC=0x1F;
	SET_BIT(PORTC,PC4);
	uint8 def[8];
    def[0]=1;

		DDRD  = 0xFF;
		PORTD = 0x00;
		EEPROM_init();
		EEPROM_writeString(0x0310,8,def);


	while(1)
    {
		UART_receiveString(key);
		EEPROM_readstring(0x0310,8,def);
		if (strcmp(def,key)==0){
			UART_sendByte(1);
			bot=UART_recieveByte();
			if(bot==1){
			SET_BIT(PORTB,PB1);
			CLEAR_BIT(PORTC,PC4);
			SET_BIT(PORTC,PC3);
			SET_BIT(PORTC,PC2);
			_delay_ms(500);
			CLEAR_BIT(PORTB,PB1);
			_delay_ms(1000);
			SET_BIT(PORTB,PB0);
			_delay_ms(500);
			CLEAR_BIT(PORTB,PB0);
			CLEAR_BIT(PORTC,PC3);
			CLEAR_BIT(PORTC,PC2);
			SET_BIT(PORTC,PC4);
		}
			else if(bot==2){
			 EEPROM_writeString(0x0310,8,def);
             UART_receiveString(def);

			}


    }
		else{
			UART_sendByte(0);
		}
		EEPROM_readstring(0x0310,8,def);
}
}
