//My Project: Trevor Scott
//directives
#include <reg51.h>

//fuction prototypes
void delay(void);
void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);

//this switches are global so I can pick and chose what I want at any moment
sbit SW1 = P0^0;
sbit SW2 = P0^1;
sbit SW3 = P0^2;
sbit SW4 = P0^3;
sbit SW5 = P0^4;
sbit SW6 = P0^5;
sbit SW7 = P0^6;
sbit SW8 = P0^7;

//my main
void main (){
	while(1){
		if(SW1){
			mode1();
		}
		if(SW2){
			mode2();
		}
		if(SW3){
			mode3();
		}
		if(SW4){
			mode4();
		}
		P1=0xff;
		delay();
		P1= 0x00;
		delay();
	}
}
void mode3(){
	unsigned char repeat0 = 0x01;
	unsigned char repeat1 = 0x80;
	unsigned char repeat2 = 0x10;
	unsigned char repeat3 = 0x08;
	char i =0;
	char j =0;
	while(SW3){
		for(i=0; i<3; i++){
			P1=(repeat1 >> i | repeat0 << i );
			delay();
		}
		for(j=0; j<3; j++){
			P1=(repeat2 << j | repeat3 >> j );
			delay();
		}
	}
}
void mode4(){
	char repeat1 = 0x80;
	char repeat0 = 0xff;
	int i =0;
	int j =0;
	while(SW4){
		for(i =0; i<7; i++){
			P1= repeat1 >> i;
			delay();
		}
		for(j=0; j<9; j++){
				P1=repeat0 << j;
				delay();
		}
	}
}
void mode1(){
	unsigned char repeat1 = 0x80;
	unsigned char repeat0 = 0x01;
	int g=0;
	int i =0;
	int j=0;
		//how many leds it must go accross minus 1 since repeat 1 and 0
		while(SW1){
		for(i =0; i <7; i++){
				P1=repeat1 >> i;
				delay();
			}
		for(j=0; j<7; j++){
			P1=repeat0 << j;
			delay();
		}
	}
}
//delay function to see the leds switch.
void delay (void){
	int i,j;
	if(SW5||SW6||SW7||SW8)
	{
	//0.5 seconds
	if(SW5){
		for(i =0; i <1000; i++){
			TMOD = 0x01;    // Timer0 mode1
			TH0 = 0xFE; 	 //initial value for 1ms
			TL0 = 0x34;
			TR0 = 1;      // timer start
			while(TF0==0);  // check overflow condition
			TR0 = 0;     // Stop Timer
			TF0 = 0;    // Clear flag
		}
	}
	//1.0 seconds
	if(SW6){
		//1000 for clock
		for(i =0; i <1000; i++){
			TMOD = 0x01;    // Timer0 mode1
			TH0 = 0xFC; 	 //initial value for 1ms
			TL0 = 0x65;
			TR0 = 1;      // timer start
			while(TF0==0);  // check overflow condition
			TR0 = 0;     // Stop Timer
			TF0 = 0;    // Clear flag
		}
	}
	//1.5s
	if(SW7){
		//1000 for clock
		for(i =0; i <1000; i++){
			TMOD = 0x01;    // Timer0 mode1
			TH0 = 0xFA; 	 //initial value for 1ms
			TL0 = 0x9A;
			TR0 = 1;      // timer start
			while(TF0==0);  // check overflow condition
			TR0 = 0;     // Stop Timer
			TF0 = 0;    // Clear flag
		}
	}
	//2s
	if(SW8){
		//1000 for clock
		for(i =0; i <1000; i++){
			TMOD = 0x01;    // Timer0 mode1
			TH0 = 0xF8; 	 //initial value for 1ms
			TL0 = 0xCC;
			TR0 = 1;      // timer start
			while(TF0==0);  // check overflow condition
			TR0 = 0;     // Stop Timer
			TF0 = 0;    // Clear flag
		}
	}
}
	else{
	//default
	for(i =0; i <1000; i++){
			TMOD = 0x01;    // Timer0 mode1
			TH0 = 0xFE; 	 //initial value for 1ms
			TL0 = 0x34;
			TR0 = 1;      // timer start
			while(TF0==0);  // check overflow condition
			TR0 = 0;     // Stop Timer
			TF0 = 0;    // Clear flag
		}
	}
}
/*
	for(i=0; i<0xff; i++){
		for(j=0; j<0xff; j++);
	*/