/*
 * final.c
 *
 *  Created on: Sep 30, 2022
 *      Author: Omar
 */
#include "keypad.h"
#include "uart.h"
#include <string.h>
uint16 bot=0,i=0,count=0,time=0,bol=1,change=0;
ISR(TIMER0_OVF_vect){
	time++;
	if (time==120){
		bol=1;

		LCD_clearScreen();
		LCD_displayString("*please enter your password*");
		 _delay_ms(500);
		 LCD_clearScreen();
		CLEAR_BIT(TIMSK,TOIE0);

	}
}
int main(void)
{
	SET_BIT(TCCR0,FOC0);SET_BIT(TCCR0,CS02);SET_BIT(TCCR0,CS00);SET_BIT(SREG,7);
	TCNT0=6;
	uint8 key[9];
	UART_init();
	LCD_init();
	LCD_sendCommand(0x01);
	LCD_displayString("*press 1 to set a password*");
	    	_delay_ms(1000);
	    	LCD_clearScreen();

    while(1)
    {
    	if(count==3){
    		SET_BIT(TIMSK,TOIE0);
    		LCD_displayString("wait 30 seconds");
    		bol=0;
    		count=0;
    	}
    	if(bol==1){
    		bot=KeyPad_getPressedKey();
    		    	if(bot==12){
    		    		key[i]='#';
    		    		UART_sendString(key);
    		    		LCD_clearScreen();
    		    		  memset(key,'\0',8*9);
    		     	      i=0;
    		    		if(change==1){
    		    			LCD_clearScreen();
    		    		   	LCD_displayString("password changed");
    		    	        _delay_ms(500);
    		     		    LCD_clearScreen();
    		     		   LCD_displayString("*please enter your password*");
    		     		  _delay_ms(500);
    		     		   LCD_clearScreen();
    		     		    change=0;
    		    		}
    		    		else{
    		    			if(UART_recieveByte()==1){
    		    	    		LCD_displayString("correct password");
    		    			    		    	_delay_ms(500);
    		    			 		LCD_clearScreen();
    		 	    		        LCD_displayString("1-open the door");
    		    			    	 LCD_displayStringRowColumn(1,0,"2-change password");
    		    			   		bot=KeyPad_getPressedKey();
    		    			  		UART_sendByte(bot);
  			    		   	if(bot==1){
    		      		        LCD_clearScreen();
    		    	  			LCD_displayString("the door is open");
    		    		_delay_ms(500);
    		    			  	LCD_clearScreen();
    		    			    		    		    }
    		    			 else if(bot==2){
    		    			    		    LCD_clearScreen();
    		    			    		    LCD_displayString("enter your new password");
    		    			    		    _delay_ms(500);
    		    	   		     		   LCD_clearScreen();
    		    			       			change=1;
    		    			    		    		    		    		}

    		    			    		    		    		    	}
    		    			   else{
    		    				   LCD_displayString("incorrect password");
    		    				      		    	  _delay_ms(500);
    		    				      		   	     LCD_clearScreen();
    		    				      		   	count++;
    		    			    		  		}
    		    			    	    	}
    		    		}

    		    	else{

    		    		key[i++]=bot;
    		    		LCD_intgerToString(bot);
    		    	}

    		    	 //get the pressed key
    		    //send the pressed key to the second MC using uart*/
    				_delay_ms(500);
    	}
    }
}

