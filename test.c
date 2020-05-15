#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte heart[8] = {
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
}; 

byte diamond[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
}; 

byte spade[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
}; 

byte club[8] = {
  B01110,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};

void setup() {
  lcd.createChar(0, heart);
  lcd.createChar(1, diamond);
  lcd.createChar(2, spade);
  lcd.createChar(3, club);
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  unsigned char randNumber=random(0,4);
  lcd.write(byte(randNumber));
  randNumber=random(0,4);
  lcd.write(byte(randNumber));
  randNumber=random(0,4);
  lcd.write(byte(randNumber));
  randNumber=random(0,4);
  lcd.write(byte(randNumber));
  _delay_ms(2000);
  lcd.clear();
  lcd.print("----");
  lcd.cursor();
}

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

void moveCursor(char taster)
{
  	unsigned char row = 0;
 	//char taster;
  	if(taster == '4')
    {
      if(row != 0)
      {
        	row--;
      		lcd.setCursor(row,0);
      }
      else if(row == 0){
      	lcd.setCursor(row,0);
      }
    }
    else if(taster == '6')
    {
      if(row != 4)
      {
        	row++;
      		lcd.setCursor(row,0);
      }
      else if(row == 4){
      	lcd.setCursor(row,0);
      }
   	}
  unsigned char simbol = 0;
  if(taster == '2')
  {
   	 simbol++;
     lcd.write(byte(simbol));
  }
  else if(taster == '8')
  {
   	 simbol--;
     lcd.write(byte(simbol));
  }
}

int main()
{
  	//lcd.begin(16, 2);
  	setup();
  	lcd.setCursor(0, 0);
	char prethodni = 0, sadasnji = 0; 
	while(1)
    { 
	  char taster = ocitaj_taster();
      //moveCursor(taster);
      if ((taster != 0) && (!prethodni && sadasnji))
      {
        moveCursor(taster);
        //lcd.print(taster);
      	//_delay_ms(500);
      }
      prethodni = sadasnji;
      sadasnji = taster;
    }
  
  	return 0;
}