/*
//Trevor Scott
//CECS 262 F @8:00am
//Project: Music
#include <reg51.h>
//this was for a delay Ineeded to get the respected 1/16,  or .2s delay
#include <intrins.h> // for _nop_()

#define uchar unsigned char
#define uint unsigned int

//my button
sbit sw1=P0^0;
sbit sw2=P0^1;
sbit sw3=P0^2;
sbit sw4=P0^3;
sbit sw5=P0^4;
sbit btn=P3^2;
sbit Buzzer=P3^7;
bit flag=1;

//this means that when reset it resets these values, keyword VOLATILE, it can work without but i figured to use it
volatile uchar th0, tl0;
uchar tl0, th0;


//prototypes
void delay();
void delay_us(uchar n_usec);
void delay_ms(uchar n_msec)	;

//my struct for music
struct music_type {
	uchar tone;
	uchar delay;
};

void playSong(struct music_type notetab[]);

//the keynotes
uint code tonetab_C[]= {62018,62401,62743,62903,63185,63441,63670,
63777,63969,64140,64216,64360,64489,64603,
64655,64751,64837,64876,64948,65012,65070};

//defns
#define C 1+7
#define D 2+7
#define E 3+7
#define F 4+7
#define G 5+7
#define A 6+7
#define B 7+7
#define C5 1+14

//for mary had a little lamb, and the gaps betweeb are for the delay such 1/16, 1.8, etc. 
//also 2nd 48
struct music_type code mary[]={
	E,0x04,D,0x04,C,0x04,D,0x04,E,0x04,E,0x04,E,0x08,
	D,0x04,D,0x04,D,0x08,E,0x04,G,0x04,G,0x08,
	E,0x04,D,0x04,C,0x04,D,0x04,E,0x04,E,0x04,E,0x08,
	D,0x04,D,0x04,E,0x04,D,0x04,C,0x012,0,0
};

//happybirthday song
//3rd 54
struct music_type code bday[]= {
	C,0x02, C,0x01,D,0x04,C,0x04,F,0x04,E,0x08,C,0x03,
	C,0x01,D,0x04,C,0x04,G,0x04,F,0x08,C,0x03,C,0x01,
	C,0x04,A,0x04,F,0x04,E,0x04,D,0x04,B,0x03,B,0x01,
	A,0x04,F,0x04,1,0,G,0x04,F,0x12,0,0
};

//twinkle and largest 4th  of the index
//86
struct music_type code twinkle[]={
	C,0x04,C,0x04,G,0x04,G,0x04,A,0x04,A,0x04,G,0x08,
	F,0x04,F,0x04,E,0x04,E,0x04,D,0x04,D,0x04,C,0x08,
	G,0x04,G,0x04,F,0x04,F,0x04,E,0x04,E,0x04,D,0x08,
	G,0x04,G,0x04,F,0x04,F,0x04,E,0x04,E,0x04,D,0x08,
	C,0x04,C,0x04,G,0x04,G,0x04,A,0x04,A,0x04,G,0x08,
	F,0x04,F,0x04,E,0x04,E,0x04,D,0x04,D,0x04,C,0x04,
	0,0};

	//jingle and smallest 1st of the index
	//48 size
struct music_type code jingle[]={
	E,0x02,E,0x02,E,0x04,E,0x02,E,0x02,E,0x04,
	E,0x02,G,0x02,C,0x02,D,0x02,E,0x08,
	F,0x02,F,0x02,F,0x04,F,0x02,E,0x02,E,0x04,
 	E,0x02,D,0x02,D,0x02,E,0x02,D,0x04,G,0x04,0,0
};
//my song and it sounds terrible 
struct music_type code mySong[]={
	E,0x04,D,0x04,B,0x03,B,0x01,C,0x04,C,0x04,G,0x04,G,0x04,A,0x04,A,0x04,G,0x08,
	E,0x08,D,0x04,D,0x04,E,0x04,D,0x04,C,0x012,0,0
};
//my main file
void main(void) {
	
	//timers are not needed but they do eliminate a pitch noise in the speakers. 
	
	TMOD = 0x01; // use timer0 mode 1 to generate tone.
	IE = 0x83; // enable timer0 overflow interrupt and interrupts
	TCON = 01; // enables IT0 for ex0
	while (1) {
		flag=1;
		if (sw1) 
			while (flag)
				playSong(mary);
		else if (sw2) 
			while (flag)
				playSong(twinkle);
		else if (sw3) 
			while (flag)
				playSong(bday);
		else if (sw4) 
			while (flag)
				playSong(jingle);
		else if (sw5) 
			while (flag)
				playSong(mySong);
		else TR0=0; // play no song
	}
}
void ex0(void) interrupt 0{
	//when a logic 0 then perform this
		flag=0;
	
}
//got this from online so that I can control my delays
void delay_us(uint n_usec)
{
  do 
  {
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
  } while (--n_usec);
}
void delay_ms(uint n_msec)	 
{
  do
    delay_us(131);
  while (--n_msec); 
}
//for speaker
void T0_ISR(void) interrupt 1  // timer0 interrupt service routine
{
  TR0=0;
  Buzzer = !Buzzer;
  TH0=th0;
  TL0=tl0;
  TR0=1;
}
//this is how I play a song
void playSong(struct music_type notetab[]) {
	uchar i, j;
	i=0;
	
	while (notetab[i].delay && flag) {
		if (!notetab[i].tone) 
			TR0 = 0; // stop tone, turn off timer0
		else {
			th0=TH0=tonetab_C[notetab[i].tone-1]>>8; // get higher 8-bit of the initial value // alt method th0=TH0=tonetab[i]/256
			tl0=TL0=tonetab_C[notetab[i].tone-1]; // get lower 8-bit of the initial value // alt method tl0=TL0=tonetab[i]/%256
			TR0=1;
		}
	 // provide duration for each tone
	 for (j=0;j<notetab[i].delay;j++)
		 delay_ms(80); // minimum delay unit for 1/16 // was 80
	 i++;
	}
	TR0=0;  // stop between songs for about 0.2s
	delay_ms(200);
}
*/

#include<reg51.h>

#define NSr 0x08
#define NSy 0x10
#define NSg 0x20

#define EWr 0x01
#define EWy 0x02
#define EWg 0x04

#define lights P1

//time period in seconds
#define gty 6 //used when any light is changing from green to yellow
#define ytr 2 //used when any light is changing from yellow to red
#define rtg 8 //used when any light is changing from red to green

void delay(int time)
{
	int i,j;
	int num = time * 10;
	for(i=0;i<num;++i)
		for(j=0;j<1275;++j);
}

void startup()
{
lights = (NSg + EWr);//NS starts green & EW starts r
}

void changeLights()
{
	if(lights == NSg + EWr)
	{
		//delay 'gty' seconds
		delay(gty);
		lights = (NSy + EWr); //NS turns yellow, EW stays red
	}
	if(lights == NSy + EWr)
	{
		//delay 'ytr' seconds
		delay(ytr);
		lights = (NSr + EWg);
	}
	if(lights == NSr + EWg)
	{
		//delay 'gty' seconds
		delay(gty);
		lights = (NSr + EWy);
	}
	if(lights == NSr + EWy)
	{
		//delay 'ytr'
		delay(ytr);
		lights = NSg + EWr;
	}
}

void main()
{
	int number = 10;
	while(1)
	{
		P1 = 0x00;
		delay(10);
		P1 = 0x1F;
		delay(10);
		startup();
		changeLights();
	}	
}



void changeLights()
{
	if(lights == NSg + EWr)
	{
		//delay 'gty' seconds
		delay(gty);
		lights = (NSy + EWr); //NS turns yellow, EW stays red
	
		//delay 'ytr' seconds
		delay(ytr);
		lights = (NSr + EWg);

		//delay 'gty' seconds
		delay(gty);
		lights = (NSr + EWy);

		//delay 'ytr'
		delay(ytr);
		lights = NSg + EWr;
	}
	else
		lights = NSg + EWr;
}



