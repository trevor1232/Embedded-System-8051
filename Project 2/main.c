#include <reg51.h>
void delay(void);
void main(void)
{
	while(1){
		//1st pattern
		P1=0x18;// turn on
		delay();
		P1=0x24;//turn off and have other leds turn on
		delay();
		P1=0x42;
		delay();
		P1=0x81;
		delay();
		P1=0x42;
		delay();
		P1=0x24;
		delay();
		P1=0x18;// turn on
		delay();
		P1=0x24;//turn off and have other leds turn on
		delay();
		P1=0x42;
		delay();
		P1=0x81;
		delay();
		P1=0x42;
		delay();
		P1=0x24;
		delay();
		P1=0x18;
		delay();
		P1=0x00;
		//2nd pattern
		delay();
		P1=0x01;
		delay();
		P1=0x02;
		delay();
		P1=0x04;
		delay();
		P1=0x08;
		delay();
		P1=0x10;
		delay();
		P1=0x20;
		delay();
		P1=0x40;
		delay();
		P1=0x80;
		delay();
		P1=0x40;
		delay();
		P1=0x20;
		delay();
		P1=0x10;
		delay();
		P1=0x08;
		delay();
		P1=0x04;
		delay();
		P1=0x02;
		delay();
		P1=0x01;
		delay();
		P1=0x02;
		delay();
		P1=0x04;
		delay();
		P1=0x08;
		delay();
		P1=0x10;
		delay();
		P1=0x20;
		delay();
		P1=0x40;
		delay();
		P1=0x80;
		delay();
		P1=0x40;
		delay();
		P1=0x20;
		delay();
		P1=0x10;
		delay();
		P1=0x08;
		delay();
		P1=0x04;
		delay();
		P1=0x02;
		delay();
		P1=0x01;
		delay();
		//my pattern below
		P1=0x80;
		delay();
		P1=0x01;
		delay();
		P1=0x80;
		delay();
		P1=0x01;
		delay();


	}
}
void delay(void)
{
	int go = 0;
	int i, j;
	for(i =0; i<0xff; i++)
		for(j =0; j<0xff; j++);
}