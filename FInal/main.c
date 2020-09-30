//Directive
#include <reg51.h>

//using simple defn for unsigned char
#define uchar unsigned char

//time period in seconds
// Defn for green, and yellow, are used when
// lights are changing, e.g. green to yellow, and yellow to red.
#define green  120 
#define yellow  40 
// walking defn is for delay in ms to use for 
// how long someone is able to walk for.
#define walk  20
unsigned char count = 0;

// The uchar variables are assigned their respected Port Pin,
// so they can be placed in their North|South or East|West wings
uchar EWr = 0x01;
uchar EWy = 0x02;
uchar EWg = 0x04;
uchar NSr = 0x08;
uchar NSy = 0x10;
uchar NSg = 0x20;

//Will assign a bit for crosswalk of their respected side they will be 
// walking on (people), when a 0 they're simply not walking yet. 
bit crossWalkNS = 0;
bit crossWalkEW = 0;

//Where the crossLight LED will be emitting it's light at,
//the port pin
sbit crossLight = P2^0;

//Prototype functions and/or predefinitions that will be used later
// WIll be used for delay
void delay(unsigned char time);
//For enabling interrupts (globally)
void Ext_int_Init();
//for chaning lights simply, green to yellow, or red to green, etc.
void changelights();

//Main 
void main(void){
	//Calling functions
	Ext_int_Init();
	//Have pre values ready for port 1
	P1 = EWr+ NSg;
	while(1){
		// always having forever changlights function active
		changelights();
	}
}

//The delay needed and intaking the ms time needed for the lights. e.g. 4s, 3s, etc
void delay(unsigned char time){
	//to use for a loop to know when to stop in miliseconds and having it 
	// become into delays of seconds (For long periods). Since of the intervals of 50ms it will just use
	// counter to keep track how many are needed to make the desired seconds.
count = 0;
 for(count=0;count<=time;count++)
  {
   TMOD=0x01;  //MODE 1 of timer
   TH0=0x4B;   // Loading high byte in TH, slows down to 50ms intervals
   TL0=0xFD;   // Loaded low byte in TL, slows down to 50ms intervals
   TR0=1;      // Running the timer
    while(TF0==0);   //for overflow
   TR0 = 0;      // If TF0=1 stop the timer
   TF0 = 0;      // Clear the Timer 
	}
}


void changelights()
{ 
	//condition statement
		if(P1 == NSg + EWr)
		{	
			crossLight = crossWalkNS;
			//delay 'gty' seconds
			delay(green);
			P1 = (NSy + EWr); //NS turns yellow, EW stays red
		}
		else if(P1 == NSy + EWr)
		{
			//This will start to toggle the light,
			// needed for blinking when light is yellow. 
			if(crossWalkNS){
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			P1 = (NSr + EWg);
			crossWalkNS = 0;
			}else{
				//delay for the color when sitting 
			delay(yellow);
			P1 = (NSr + EWg);}
		}
		else if(P1 == NSr + EWg)
		{	
			crossLight = crossWalkEW;
			//delay 'gty' seconds
			delay(green);
			P1 = (NSr + EWy);

		}
		else if(P1 == NSr + EWy)
		{
			if(crossWalkEW){
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			delay(10);
			crossLight =~crossLight;
			P1 = NSg + EWr;
			crossWalkEW=0;
			}else{
			delay(yellow);
			P1 = NSg + EWr;}
		}
}


void Ext_int_Init()				
{
	EA  = 1;	/* Enable global interrupt */
	EX0 = 1;      	/* Enable Ext. interrupt0 */
	IT0 = 1; 
	IT1=1;
	EX1=1;/* Select Ext. interrupt0 on falling edge */
}

//For external interrupt to be active for button
// When pressed it will active the crosswalk, and have the lights be ready. 
void walk_EastWest() interrupt 2
{
	if(P1 == EWr+NSg){
		count = 100;
		crossWalkEW=1;
	}
}

// Needed to have external interrupt for the button
// When pressed it will active the crosswalk, and have the lights be ready. 
void walk_NorthSouth() interrupt 0
{
	if(P1 == EWg+NSr){
		count = 100;
		crossWalkNS=1;
	}
}

