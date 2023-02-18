#include "HX711.h"  //You must have this library in your arduino library folder
#define DOUT  A2
#define CLK    A3
#include  <Wire.h>
#include <LiquidCrystal_I2C.h>

HX711 scale;

LiquidCrystal_I2C lcd(0x27 , 2 , 1, 0, 4, 5, 6, 7, 3, POSITIVE);

float calibration_factor = 1000; // this calibration factor is adjusted according to my load cell
float units;

const int buttonPin = A1; 
int buttonState = 0;
int button=0;
int state=0;

const int buzzer = 8; //buzzer to arduino pin 9
int sensor = 0;

void setup(){
  Serial.begin(9600);
  lcd.begin(20,4);
  pinMode(buttonPin, INPUT);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  scale.tare();  //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

 int num=0;
 
void loop(){
 float p;
 int c=0;
 int check=0;
 int w;
 int l=0;
 int l1;
 int l2;
 int button =0;
 int count;
 int number;

 

 lcd.setCursor(3,0);
 lcd.print("Off       ");
 lcd.setCursor(3,1);
 lcd.print("             ");
 buttonState = digitalRead(buttonPin);
 if (buttonState == HIGH)
 {
  button++;
  tone(buzzer,1000);
  delay(1000);
  noTone(buzzer);
  delay(4000);
   number=2; 
   count = 0;
 }

 if (button!=0)
 {
  state = 1;
  
 }
Serial.print(button);
 while (num/2==0 && state != 0)
 {
   w=0;
   for (int i=0;i<2;i++)
   {
     tone(buzzer,1000);
     delay(1000);
   }
   tone(buzzer, 1000);
   delay(1500);
   c=0;
   w=0;
   while (w==0 && l!=1)
   {
      if (number==5)
      {
        number=2;
      }
      for (int i=0;i<3;i++)
      {
         buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH)
        {
          l=1;
          noTone(buzzer);
          break;
        }
        units = scale.get_units(), 5;
        if (units < 0)
        {
          units = 0.00;
        }  
        if (units > 0 && count ==0)
        {
          scale.tare();
          count++;
        }
  //      Serial.print("Weight: ");
        lcd.setCursor(3,0);
        lcd.print("Weight     ");
        lcd.setCursor(3,1);
        lcd.print(units,5);
        lcd.print(" grams     ");
  //      Serial.print(units, 5); //displays the weight in 4 decimal places only for calibration
  //      Serial.print("grams");
  //      Serial.println(); 
        noTone(buzzer);     // Stop sound...
        delay(3000);        // ...for 1sec  
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000); 
      } 
    Serial.println(number);
    if (number==2)
    {
      if (units <900)
      {
        w=0;
        delay(1000);  
      }
      else 
      {
        w=1;
        delay(1000);
      }
    }
    if (number==3)
    {
      if (units > 650 && units <850)
      {
        w=0;
        delay(1000);  
      }
      else 
      {
        w=1;
        delay(1000);
      }
    }
    if (number==4)
    {
      if (units > 400 && units <600)
      {
        w=0;
        delay(1000);  
      }
      else 
      {
        w=1;
        delay(1000);
      }
    }
   }
  
   Serial.print("nakalusot");
   Serial.println();
   Serial.print(l);
   noTone(buzzer);

   if (l!=0)
   {
    state = 0;
    break;
   }
   p=(units); 
  
   if (p>900)
   {
    c=1;
    number=3;
   }
   else if(p>650 && p<850)
   {
    c=2;
    number=4;
   }
   else if (p>400 && p<600)
   {
    c=3;
    number=5;
   }
  
   Serial.print(number);
   Serial.println();
   l1=0;
   if (c==1)
   {
    for(int i=0;i<10;i++)
    {
    buttonState = digitalRead(buttonPin);
      lcd.setCursor(3,0);
      lcd.print("Waiting");
      lcd.setCursor(3,1);
      lcd.print(p);
      lcd.print(" grams     ");
      if (buttonState == HIGH)
      {
        Serial.println("off");
        l1=1;
        break;
       }
      delay(1000);  
    }
   }
   else
   {
     for (int i=0;i<7200;i++)
     {
      buttonState = digitalRead(buttonPin);
        lcd.setCursor(3,0);
        lcd.print("Waiting");
        lcd.setCursor(3,1);
        lcd.print(p);
        lcd.print(" grams     ");
      if (buttonState == HIGH)
      {
        Serial.println("off");
        l1=1;
        break;
      }
      delay(1000);
     }
   }
   lcd.setCursor(3,0);
        lcd.print("Waiting");
        lcd.setCursor(3,1);
        lcd.print(p); 
  Serial.print("nabreak");
   check = 0;
   tone(buzzer,1000);
   delay(1000);
   noTone(buzzer);
   delay(1000);
   if (l1!=0)
   {
    state=0;
    break;
   }
   l2=0;
   check=0;
   
   for (int i=0;;i++)
   {
    buttonState = digitalRead(buttonPin);
    Serial.print(check);
    if (buttonState == HIGH)
    {
      Serial.println("off");
      l2=1;
      break;
    }
    tone(buzzer,1000);
    units = scale.get_units(), 5;
    if (units < 0)
    {
      units = 0.00;
    }
    lcd.setCursor(3,0);
      lcd.print("Weight: ");
      lcd.print(units,5);
      lcd.print(" grams     ");   
      lcd.setCursor(0,1);
      lcd.print("                          ");
      lcd.setCursor(0,2);
      lcd.print("                             ");
    if (c==1)
    {
      if (units >650 && units <850)
      {
        check = 1; 
        break;
      }
    }
    else if (c == 2)
    {
      if (units >400 && units <600)
      {
        check = 1;
        break;
      }
    }
    else if(c==3)
    {
      if (units > 150 && units < 350)
      {
        check = 1;
        break;
      }
    }
      lcd.setCursor(3,0);
      lcd.print("Weight: ");
      lcd.print(units,5);
      lcd.print(" grams     "); 
  
    delay(2000);
   }

   delay(5000);
   if (l2!=0)
   {
    state=0;
    noTone(buzzer);
    break;
   }
 }
   Serial.print("balik");

 
}
