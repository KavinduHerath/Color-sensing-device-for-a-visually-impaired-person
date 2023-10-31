/* This code works with GY-31 TCS3200 TCS230 color sensor module
 * It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays it on the Serial monitor
 * Refer to www.surtrtech.com for more details
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define s0 8       //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12

int data=0;        //This is where we're going to stock our values
int Red=0, Blue=0, Green=0;

void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%

   lcd.init();
   lcd.backlight();
}

void loop()                  //Every 2s we select a photodiodes set and read its data
{
   lcd.begin(16, 2);
   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red value= "); 
   GetData();                 //Executing GetData function to get the value
   Red=data;

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   GetData();
   Green=data;

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue value= ");
   GetData();
   Blue=data;

   Serial.println();

   delay(2000);

   //GetColors();                                     //Execute the GetColors function to get the value of each RGB color
                                                   //Depending of the RGB values given by the sensor we can define the color and displays it on the monitor

   //if (Red <=15 && Green <=15 && Blue <=15)         //If the values are low it's likely the white color (all the colors are present)
   if (Red > 8 && Red < 18 && Green > 9 && Green < 19 && Blue > 8 && Blue < 16)   
      //Serial.println("White");
      lcd.print("White");                    
      
   //else if (Red<Blue && Red<=Green && Red<23)      //if Red value is the lowest one and smaller thant 23 it's likely Red
   else if (Red > 12 && Red < 30 && Green > 40 && Green < 70 && Blue > 33 && Blue < 70)   
      //Serial.println("Red");
      lcd.print("Red");

   //else if (Blue<Green && Blue<Red && Blue<20)    //Same thing for Blue
   else if (Red > 65 && Red < 125 && Green > 65 && Green < 115 && Blue > 32 && Blue < 65)
      //Serial.println("Blue")
      lcd.print("Blue");

   //else if (Green<Red && Green-Blue<= 8)           //Green it was a little tricky, you can do it using the same method as above (the lowest), but here I used a reflective object
   else if (Red > 50 && Red < 95 && Green > 35 && Green < 70 && Blue > 45 && Blue < 85)   
      //Serial.println("Green");                    //which means the blue value is very low too, so I decided to check the difference between green and blue and see if it's acceptable
      lcd.print("Green");

   else if (Red > 10 && Red < 20 && Green > 10 && Green < 25 && Blue > 20 && Blue < 38)
      //Serial.println("Yellow");
      lcd.print("Yellow");

   else if (Red > 80 && Red < 125 && Green > 90 && Green < 125 && Blue > 80 && Blue < 125)
      //Serial.println("Black");
      lcd.print("Black");

   else if (Red > 26 && Red < 34 && Green > 24 && Green < 32 && Blue > 39 && Blue < 47)   
      //Serial.println("Light Green");
      lcd.print("Light Green");

   else if (Red > 18 && Red < 26 && Green > 30 && Green < 38 && Blue > 40 && Blue < 50)   
      //Serial.println("Drak Yellow");                    
      lcd.print("Dark Yellow");

   else if (Red > 26 && Red < 34 && Green > 60 && Green < 72 && Blue > 56 && Blue < 66)   
      //Serial.println("Orange");
      lcd.print("Orange");

   else if (Red > 40 && Red < 48 && Green > 42 && Green < 50 && Blue > 26 && Blue < 34)   
      //Serial.println("Purple");
      lcd.print("Purple");
      s
   else
      //Serial.println("Unknown");
      lcd.print("Unknown");
}

void GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
}

//void GetColors()  
/*{    
   digitalWrite(s2, LOW);                                           //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green 
   digitalWrite(s3, LOW);                                           
   Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again, if you have trouble with this expression check the bottom of the code
   delay(20);  
   digitalWrite(s3, HIGH);                                         //Here we select the other color (set of photodiodes) and measure the other colors value using the same techinque
   Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
   delay(20);  
   digitalWrite(s2, HIGH);  
   Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
   delay(20);  
}*/
