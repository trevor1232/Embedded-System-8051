#include <reg51.h>
#define uchar unsigned char

sbit SW1= P0^0; sbit SW2= P0^1;
//interupter
sbit SW8= P0^7;

//function prototypes void delay(void);
void PARTCP1(void); void PARTCP2(void); 
void main(void) {
///////For Part A)//////////
/*
unsigned char mynum[] = "ABCDEF"; // RAM Space unsigned char z;
while(1){
for(z=0; z<=6; z++){
P1=mynum[z];
}
}
*/
/*
unsigned char mydata[100]; //RAM sapce unsigned char x,z=0; for(x=0;x<100;x++){
z--;
mydata[x]=z; P1=z;
delay();
}
 
*/
////////////////////////////
/////Part B)//////////////

//intel text file below

/*
unsigned char my_data0[] = {0x08, 0x08, 0x0c, 0x00, 0x75, 0x80, 0xff, 0x85, 0x80, 0x90, 0x80, 0xf8};//size 12
unsigned char my_data1[] = {0x03,0x00,0x00,0x00,0x02,0x08,0x00};// size 7
unsigned char my_data2[] = {0x0c, 0x08, 0x00, 0x00, 0x78, 0x7f, 0xe4,0xf6, 0xd8, 0xfd, 0x75, 0x81,0x07, 0x02, 0x08, 0x0c}; //16 size
unsigned char my_data3[] = {0x00, 0x00, 0x00, 0x01}; //size 4

unsigned char good= 'G'; unsigned char bad='B'; unsigned char x; unsigned char sum = 0;
unsigned char checksumbyte0; unsigned char checksumbyte1; unsigned char checksumbyte2; unsigned char checksumbyte3;

unsigned char checkSum0=0xe3; unsigned char checkSum1=0xf3; unsigned char checkSum2=0x33; unsigned char checkSum3=0xff;
P2=~0xc0; P1=~0xc0;

//1
for(x=0; x<12; x++)
{
sum = sum + my_data0[x]; //add them together
}

checksumbyte0 = ~sum +1; // 2's complement
//reset sum sum =0;

//2
for(x=0; x<7; x++)
{
sum = sum + my_data1[x]; //add them together
}

checksumbyte1 = ~sum +1; // 2's complement sum=0;
 

//3
for(x=0; x<16; x++)
{
sum = sum + my_data2[x]; //add them together
}

checksumbyte2 = ~sum +1; // 2's complement sum=0;

//4
for(x=0; x<4; x++)
{
sum = sum + my_data3[x]; //add them together
}

checksumbyte3 = ~sum +1; // 2's complement sum=0;

//if else statement
if(checkSum0 == checksumbyte0 && checkSum1 == checksumbyte1 && checkSum2 == checksumbyte2 && checkSum3 == checksumbyte3){
//Segments showing G or B are just a bonus and I put the delay just to see how quick it compiles the DATA.
	P1=~0xc0; 
	delay(); 
	P2=~0x82;
	delay(); 
	P0=good;
} else {
	P1=~0xc0; 
	delay(); 
	P2=~0x80;
	delay(); 
	P0=bad;
}
*/
//partc
while(1){
if(SW1){
PARTCP1();
} if(SW2){
	PARTCP2();
} else {
	P1=~0x80; P2=~0x80;
}
}
}
void PARTCP@(voidi) {
	unsigned char my_data0[] = {0x08, 0x08, 0x0c, 0x00, 0x75, 0x80, 0xff, 0x85, 0x80, 0x90, 0x80, 0xf8};//size 12
unsigned char my_data1[] = {0x03,0x00,0x00,0x00,0x02,0x08,0x00};// size 7
unsigned char my_data2[] = {0x0c, 0x08, 0x00, 0x00, 0x78, 0x7f, 0xe4,0xf6, 0xd8, 0xfd, 0x75, 0x81,0x07, 0x02, 0x08, 0x0c}; //16 size
unsigned char my_data3[] = {0x00, 0x00, 0x00, 0x01}; //size 4

unsigned char good= 'G'; unsigned char bad='B'; unsigned char x; unsigned char sum = 0;
unsigned char checksumbyte0; unsigned char checksumbyte1; unsigned char checksumbyte2; unsigned char checksumbyte3;

unsigned char checkSum0=0xe3; unsigned char checkSum1=0xf3; unsigned char checkSum2=0x33; unsigned char checkSum3=0xff;
P2=~0xc0; P1=~0xc0;
 


 

