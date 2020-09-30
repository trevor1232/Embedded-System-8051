//Trevor Scott
//So this program I did get outsource material to do as far as I did, and about half I was able to code. I just want to be absoutely try about it. 

//Directives
#include <reg51.h>
#include <absacc.h>
#include <ctype.h> // toUpper

#define uchar unsigned char
#define uint  unsigned int	
//ADDRESSES
uchar START_ADDR[5];  
uchar END_ADDR[5];

#define CR 0x0D   //Signifies \r "return"
#define LF 0x0A   //Signifies beginning of line

void Mem_Write(uint i, uint mode);
uchar rw_in_check(uchar user_menu);
void read_mem(uchar mem_value, uchar *value_str);
uint adder_check(uchar user_menu, uint i, uint start);
void trans_a_char(uchar mychar);
void update_output(uint i, uchar RW);
void init_serial();
void send_1_line(uchar *line_out);
uchar Receive_Char();
void receive_1_line(uchar *line_in);
uint hex_str_to_value(uchar *hex_str);

//Main
void main(void){
  uchar code start_msg[] =
  {"This program allows you access different parts of memory areas in the 8051.\n\r\r"};
  uchar code menu[] =
  {"\n\r\rChoose a memory area to access: \n\r\r1. Internal RAM\n\r\r2. Flash ROM\n\r\r3. Expanded RAM\n\r"};
	//will get the user's choice
  uchar user_RW;
  uchar user_menu = 0;
  uchar reloop = 0;  
  uint start_addr, end_addr, i;

  //Memory location is 8-bits thus we only need 2 hex digits,
	// to access memory address(s)
  uchar mem_hex_val[4];
  init_serial();
  send_1_line(start_msg);         
  while(1){
    if(!reloop){
			//Outputs the menu
      send_1_line(menu);                   
			//Receives user's  choice
      user_menu  = Receive_Char();         
			//Checks Read write input
      user_RW    = rw_in_check(user_menu); 
      start_addr = adder_check(user_menu, 0, 0);
      end_addr   = adder_check(user_menu, 1, start_addr);
    }
		//for Read only
    else user_RW = 'R';
      
    //Read or write data from specified memory 
    //and send them to serial port for the respected memory access
    for(i=start_addr; i<=end_addr; i++){
      switch(user_menu){
        case '1':
          if(toupper(user_RW)=='W') Mem_Write(i, 1);
          if(i==end_addr && toupper(user_RW)=='W'){
            update_output(1, 'W');
            reloop = 1;
          }
          if(i==start_addr && toupper(user_RW)=='R' && !reloop){
            update_output(1, 'R');
          }
          if(toupper(user_RW)=='R'){
            reloop = 0;
            read_mem(DBYTE[i], mem_hex_val);
          }
          break;
        case '2':
          user_RW = 'R';
          if(i==start_addr) 
            update_output(2, 'R');
          read_mem(CBYTE[i], mem_hex_val);
          break;
        case '3':
          if(toupper(user_RW)=='W') Mem_Write(i, 3);
          if(i==end_addr && toupper(user_RW)=='W'){
            update_output(3, 'W');
            reloop = 1;
          }
          if(i==start_addr && toupper(user_RW)=='R' && !reloop)
            update_output(3, 'R');
          if(toupper(user_RW)=='R'){
            reloop = 0;
            read_mem(XBYTE[i], mem_hex_val);
          }
        default:
          break;
      }
      if(!reloop && toupper(user_RW) == 'R')
        send_1_line(mem_hex_val);  
    }
    if(!reloop) send_1_line("\n\r\n\r");
  }
}

// This function displays outputs depending on whether the
// user read or wrote for the memory they selected
void update_output(uint i, uchar RW){
  const uchar *prompt[5];
  prompt[0] = "\n\rThe contents in Internal RAM locations ";
  prompt[1] = "\n\rThe contents in Flash ROM locations ";
  prompt[2] = "\n\rThe contents in Expanded RAM locations ";
  prompt[3] = " - ";
  prompt[4] = " are updated with: ";
  prompt[5] = " are: ";
    
  if(RW=='R'){
    if(i==1) send_1_line(prompt[0]);
    if(i==2) send_1_line(prompt[1]);
    if(i==3) send_1_line(prompt[2]);
    send_1_line(START_ADDR);
    send_1_line(prompt[3]);
    send_1_line(END_ADDR);
    send_1_line(prompt[5]);
  }
  else{
    if(i==1) send_1_line(prompt[0]);
    if(i==3) send_1_line(prompt[2]);
    send_1_line(START_ADDR);
    send_1_line(prompt[3]);
    send_1_line(END_ADDR);
    send_1_line(prompt[4]);
  }
}

// This function checks the starting and ending address of
// what the user inputs
uint adder_check(uchar user_menu, uint i, uint start){
  uint range, value;
  uint min=0;
  const uchar *prompt[3];
  prompt[0] = "\n\rEnter a starting address in hex(Ex: 70):";
  prompt[1] = "\rEnter an ending address in hex(Ex: 73):";
  prompt[2] = "\rAddress is invalid. Re-enter";

  if(user_menu == '1'){
		range=0xFF; min=0x30;
	}
  else if(user_menu == '2') {
		range=0xFFFF;
	}
  else if(user_menu == '3') {
		range=0x6FF;
	}
	else{
		return 0;
	}
  send_1_line(prompt[i]);
  if(i==0){
    receive_1_line(START_ADDR);
    value=hex_str_to_value(START_ADDR);
  }
  else{
    receive_1_line(END_ADDR);
    value=hex_str_to_value(END_ADDR);
  }
  while((value > range || value < min) || (value < start && i)){
    send_1_line(prompt[2]);
    adder_check(user_menu, i, start);
  }
  return value;
}

// This function checks if the user entered R or W for read or
// write option in menu
uchar rw_in_check(uchar user_menu){
  uchar code read_write[] = 
  {"\n\rEnter R for read or W for write)\n\r"};
  uchar code invalid_input[] =
  {"\n\rInvalid choice\n\r"};
  uchar RW;
  
  //This checks if user chose option 1 or 3 and then asks if
  //they want to read or write and checks the input
  if(user_menu == '1' || user_menu == '3'){
    send_1_line(read_write);
    RW = Receive_Char();
    while(toupper(RW) != 'W' && toupper(RW) != 'R'){
      send_1_line(invalid_input);
      rw_in_check(user_menu);
    }
    trans_a_char(RW);
    return RW;
  }
  return 0; //Returns 0 if user chooses option 2
}

// This function transmits a char data member
void trans_a_char(uchar mychar){
   SBUF=mychar;
   while (TI==0); // wait until transmitted
   TI=0;
}

// Initial serial port to work with a 9600 baud rate 
void init_serial(void){
  TMOD = 0x20;
  TH1  = 0xFD;
  SCON = 0x50;
  TR1  = 1;
}

// This function outputs a line to be displayed for the user
void send_1_line(uchar *line_out){
  while(*line_out != 0x00){
    SBUF = *line_out;
    while(!TI);
    TI = 0;
    line_out++;
  }
}

// This function finds out the hex string that represent the
// specified memory value. 
void read_mem(uchar mem_value, uchar *value_str){
  //Calculate and find the ASCII value for the high hex digit
  value_str[0]=(mem_value&0xF0)>>4;
  value_str[0]=value_str[0]>9?value_str[0]-10+'A':value_str[0]+'0';

  //Calculate and find the ASCII value for the low hex digit
  value_str[1]=mem_value&0x0F;
  value_str[1]=value_str[1]>9?value_str[1]-10+'A':value_str[1]+'0';

  //Add a space for display format control, and a null terminator for the string
  value_str[2] = ' ';
  value_str[3] = '\0';
}

//this will write the memory into the internal ram memory
void Mem_Write(uint i, uint mode){
  uchar write[5]; 
  uchar code write_prompt[] =
  {"\n\rPlease enter new data in hex:" };
  send_1_line(write_prompt);
  receive_1_line(write);
  if(mode==1) DBYTE[i] = hex_str_to_value(write);
  if(mode==3) XBYTE[i] = hex_str_to_value(write);
}



// This function receives one char to choose a menu choice 
uchar Receive_Char(){
  uchar received_char;
  while(!RI);
  received_char = SBUF;
  RI            = 0;
  return received_char;
}

// This function recieves a string of chars
void receive_1_line(uchar *line_in){
  uchar received_line;
  do{
    while(!RI);
    received_line = SBUF;
    *line_in      = received_line;
    line_in++;
    RI            = 0;
  }while(received_line != CR); //While not at end line
  
  //Transmits LF char
  SBUF=LF;
  while (!TI); //Wait until transmitted
  TI=0;
  
  //Remove CR and add null terminator to the string
  line_in--;
  *line_in = '\0'; 
}




// This function converts a hex digit string to its
// equivalent hex value.
uint hex_str_to_value(uchar *hex_str){
  uchar c;
  uint value=0;
  uchar index=0;
  
  //Calculate the hex value
  while (c=toupper(hex_str[index++]))
    if (c>='0' && c<='9')
      value = (value<<4)+(c-'0');
    else if ((c>='A' && c<='F')||(c>='a' && c<='f'))
      value = (value<<4)+(c-'A'+10);
    else 
      return 0; //Wrong hex number
  return value; //Right hex number
}





