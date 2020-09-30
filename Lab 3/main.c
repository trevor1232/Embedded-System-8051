//My Lab3: Trevor Scott
//directives
#include <reg51.h>

//fuction prototypes
void count(void);
void delay(void);
void myLoop(void);

//this switches are global so I can pick and chose what I want at any moment
sbit SW1 = P0^0;
sbit SW2 = P0^1;
sbit SW3 = P0^2;
sbit SW4 = P0^3;
sbit SW5 = P0^4;
sbit SW6 = P0^5;

//my main
void main (void){

	while(1){
		if(SW1){
			count();
		}
		//a logic gate requiring sw1 and s2 and s3
		if(SW6&SW5&SW4){
			P1 = 0x01;
		}
		if(SW3){
			myLoop();
		}
	else{
			//This will keep the leds low active
			P1 = 0X00;
		}
	}
}
void count(void){
	//8-bit char
	unsigned char x = 0x00;
	//counting upward with this program for sw1
	while(SW1){
		P1 = x;
		delay();
		x+=0x01;// x = x + 1
	}
}
//My pattern
void myLoop(void){
	unsigned char x1 = 0x01;
	while(SW3){
		P1=x1;
		x1^=0x81;
		delay();
	}
}

//delay function to see the leds switch.
void delay (void){
	int i,j;

	for(i=0; i<0xff; i++){
		for(j=0; j<0xff; j++);
	}
}