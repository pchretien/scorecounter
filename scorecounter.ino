#include <avr/power.h>

// Shitf registers pin-out
#define SER_Pin 2
#define RCLK_Pin 3
#define SRCLK_Pin 4
 
// Buttons pin-out
#define BUTTON1 0
#define BUTTON2 1

// Sleep time between each digit
#define DISPLAY_DELAY 2

// Number of shift regiters
#define nbICs 2 
#define maxArraySize nbICs * 8 
boolean registers[maxArraySize];

int buttonPin[2] = {BUTTON1, BUTTON2};
int buttonCount[2] = {0,0};
int score[2] = {0,0};
 
void setup()
{
  if (F_CPU == 16000000) 
    clock_prescale_set(clock_div_1);
  
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}       
 
void loop()
{  
  
  checkButton(0);
  checkButton(1); 
  
  //displayLargeInt((score[0]*100)+score[1]);
  displayHourMinute(score[0], score[1], true);
}

void checkButton(int buttonIndex)
{    
  if(digitalRead(buttonPin[buttonIndex])==LOW)
  {
    if(buttonCount[buttonIndex] > 200)
      score[buttonIndex] = 0;
    else if(buttonCount[buttonIndex] > 30)
      score[buttonIndex] = score[buttonIndex] - 1;
    else if(buttonCount[buttonIndex] > 2)
      score[buttonIndex] = score[buttonIndex] + 1;
      
    buttonCount[buttonIndex] = 0;
  }
  else
  {
    buttonCount[buttonIndex] = buttonCount[buttonIndex] + 1;
    
    if(buttonCount[buttonIndex] > 200)
    {
      score[buttonIndex] = 0;
    }
  }
}
 
// Set all pins to LOW
void clearRegisters()
{
  for(int i = maxArraySize - 1; i >=  0; i--)
     registers[i] = LOW;
} 
 
// Write the bits to the register(s) output pins
void writeRegisters()
{ 
  digitalWrite(RCLK_Pin, LOW);
 
  for(int i = maxArraySize - 1; i >=  0; i--)
  {
    digitalWrite(SRCLK_Pin, LOW);
 
    int val = registers[i];
 
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
 
  }
  
  digitalWrite(RCLK_Pin, HIGH); 
}

void setRegisterPin(int index, int value)
{
  registers[index] = value;
}

void displayHourMinute(int hours, int minutes, boolean dots)
{
  int digit4 = minutes%10;
  displayDigit(4, digit4);
  
  int digit3 = (minutes >= 10)?(minutes%100)/10:-1;
  displayDigit(3, digit3);
  
  if(dots)
    displayHourDots();
  
  int digit2 = hours%10;
  displayDigit(2, digit2);
  
  int digit1 = (hours>=10)?(hours%100)/10:-1;
  displayDigit(1, digit1);
}

void displayLargeInt(int value)
{
  int digit4 = value%10;
  displayDigit(4, digit4);
  
  int digit3 = (value>=10)?(value%100)/10:-1;
  displayDigit(3, digit3);
  
  int digit2 = (value>=100)?(value%1000)/100:-1;
  displayDigit(2, digit2);
  
  int digit1 = (value>=1000)?(value%10000)/1000:-1;
  displayDigit(1, digit1);
}

void displayDigit(int digit, int value)
{
  clearRegisters();
  writeRegisters();  
  setInt(digit, value);
  writeRegisters();  
  delay(DISPLAY_DELAY);
}

void displayHourDots()
{
  clearRegisters();
  writeRegisters();  
  setRegisterPin(0, HIGH);
  setRegisterPin(8, HIGH);
  writeRegisters();   
  delay(DISPLAY_DELAY);
}

void setInt(int digit, int value)
{
  switch(value)
  {
    case 0:
      set_0(digit);
      break;
    case 1:
      set_1(digit);
      break;
    case 2:
      set_2(digit);
      break;
    case 3:
      set_3(digit);
      break;
    case 4:
      set_4(digit);
      break;
    case 5:
      set_5(digit);
      break;
    case 6:
      set_6(digit);
      break;
    case 7:
      set_7(digit);
      break;
    case 8:
      set_8(digit);
      break;
    case 9:
      set_9(digit);
      break;
    default:
      setRegisterPin(digit, HIGH); // Turn digit off
      break;
  }
}

void set_0(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(9, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(15, HIGH);  
}

void set_1(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);  
}

void set_2(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(9, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
}

void set_3(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
}

void set_4(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);
}

void set_5(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);
}

void set_6(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(9, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);
}

void set_7(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
}

void set_8(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(9, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);
}

void set_9(int digit)
{
  setRegisterPin(digit, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);
}
