#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//On arduino UNO:       A4(SDA), A5(SCL)

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define s0 8       //TCS3200 pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12

int data=0, Red=0, Green=0, Blue=0;
String strColor;
String strRed;
String strGreen;
String strBlue;
String str1;
String str2;

void setup(){
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextColor(WHITE);     // text color

  strColor=String("White");
  
  pinMode(s0,OUTPUT);    //pin modes
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);

  Serial.begin(9600);   //intialize the serial monitor baud rate
   
  digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
  digitalWrite(s1,LOW); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
}

void loop() {
  oled.clearDisplay(); // clear display
  digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  digitalWrite(s3,LOW);

  Serial.print("Red value= "); 
  GetData();                 //Executing GetData function to get the value
  data = map(data, 505, 106, 0, 255);
  Red=data;
  strRed=String(Red);

  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);

  Serial.print("Green value= ");
  GetData();
  data = map(data, 485, 102, 0, 255);
  Green=data;  
  strGreen=String(Green);

  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);

  Serial.print("Blue value= ");
  GetData();
  data = map(data, 360, 75, 0, 255);
  Blue=data;
  strBlue=String(Blue);

  Serial.println();
  delay(2000);

  //getColor();

  displayColor();
  displayRed();
  displayGreen();
  displayBlue();
}

void displayColor(){
  oled.setTextSize(2);          // text size
  oled.setCursor(0, 0);         // position to display
  oled.print(strColor);   // text to display
  oled.display();               // show on OLED
}

void displayRed(){
  oled.setTextSize(1);          // text size
  oled.setCursor(0, 25);        // position to display
  str1=String("Red: ");       // text to display
  str2=String(str1+strRed);
  oled.print(str2);
  oled.display();               // show on OLED
}

void displayGreen(){
  oled.setTextSize(1);          // text size
  oled.setCursor(0, 38);        // position to display
  str1=String("Green: ");       // text to display
  str2=String(str1+strGreen);
  oled.print(str2);
  oled.display();               // show on OLED
}

void displayBlue(){
  oled.setTextSize(1);          // text size
  oled.setCursor(0, 51);        // position to display
  str1=String("Blue: ");       // text to display
  str2=String(str1+strBlue);
  oled.print(str2);
  oled.display(); 
}

void GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
}