#include"Header.h"
// LCD module control pins and data bus definitions 
#define LCD_E_PIN          0x08
#define LCR_RW_PIN         0x10
#define LCD_RS_PIN         0x20
#define LCD_DATA_BUS       GPIO_PORTB_DATA_R
#define LCD_CONTROL_BUS    GPIO_PORTE_DATA_R

/* This function initializes Port B and pins 3,4 and 5 of Port E  
   as digital outputs. */
void GPIO_Port_Init(void)
{	
 //Clock Gating Control
  RCGC_GPIO_R |= 0x12;     //enable clock for Port B & E
	
	//GPIO configuration for Port B
	GPIO_PORTB_DIR_R |= 0xFF;     // Port B as output
	GPIO_PORTB_DEN_R |= 0xFF;     // digital enable
	GPIO_PORTB_AFSEL_R &= ~0xFF;  // regular port function
	
	//GPIO Configuration for Port E pins 3, 4 and 5
	GPIO_PORTE_DIR_R |= 0x38;     // Port E pins as output
	GPIO_PORTE_DEN_R |= 0x38;     // digital enable
	GPIO_PORTE_AFSEL_R &= ~0x38;  // regular port function
	
	// GPIO_Init();    
	LCD_Init();
	LCD_Clear();
}

/* This function writes user command to the LCD module. */
void LCD_Send_Command(unsigned char command)
{
	LCD_DATA_BUS = command;
	LCD_CONTROL_BUS = 0;
	
	// Generate a pulse on the LCD Enable pin
	Delay(10);                     
	LCD_CONTROL_BUS |= LCD_E_PIN;                 
	Delay(40);                     
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(40); 
}

/* This function writes user data to the LCD module. */
void LCD_Send_Data(unsigned char data)
{
	LCD_DATA_BUS = data;
	LCD_CONTROL_BUS = LCD_RS_PIN;
	
	// Generate a pulse on the LCD Enable pin
	Delay(10);                     
	LCD_CONTROL_BUS |= LCD_E_PIN;                 
	Delay(40);                     
	LCD_CONTROL_BUS &= ~(LCD_E_PIN);
	Delay(40);                     
}

/* This function initializes the LCD module for 8-bit data 
   interface, turns ON the display and cursor. */
void LCD_Init(void)
{
	LCD_CONTROL_BUS = 0;             
	Delay(15000);                    // Wait for approx. 15ms 
	
	// Configure LCD for required functionality
	LCD_Send_Command(0x38);         // Function Set: 8 bit, 2 line
	LCD_Send_Command(0x10);         // Set cursor
	LCD_Send_Command(0x0E);         // Display ON, cursor ON
	LCD_Send_Command(0x06);         // Entry mode
}

/* This function clears LCD module and brings cursor to home 
   position on the display. */
void LCD_Clear(void)
{
	LCD_Send_Command(0x01);   // Clear display
	Delay(1700);               // Delay for approx. 1.6ms
	LCD_Send_Command(0x02);   // Move cursor to home
	Delay(1700);               // Delay for approx. 1.6ms
}

/* This function writes character string to LCD display. */
void LCD_Send_String(char *ptr){
  while(*ptr){
    LCD_Send_Data(*ptr);
    ptr++;
  }
}

/* This function moves the cursor to (x,y) coordinates on 
   the LCD display. */
void LCD_Goto_XY(unsigned char x, unsigned char y)
{
	unsigned char row_start_address[] = {0x80, 0xC0}; 

  // Move cursor to (x,y) location on display
	LCD_Send_Command(row_start_address[y-1] + x - 1); 
	Delay(1700);              // Delay for approx. 1.6ms	
}


/* This function generates the delay. */

void Delay(unsigned long int period)
{
	int i=0;
	for(i=0;i<12*(period/10);i++);
}	

int Binary2Decimal(int Bit_L, int Bit_H, unsigned int Binary[])
{
	int temp=0,i;
	for(i = Bit_L;i<Bit_H;i++)
	temp += Binary[i] * (1<<((Bit_H-1)-i));
	return temp;
}
/*
void Binary2Hex(unsigned char Hex[], unsigned int Binary[])    
{ 
	unsigned int temp=0;
	char Dec2Hex[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	int i,j=0;
	for(i=0;i<40;){ 
		temp += Binary[i]*(1<<(3-(i%4)));
		if(++i%4 == 0){
			Hex[j++] = Dec2Hex[temp];
			temp = 0;
		}
	}
}*/
