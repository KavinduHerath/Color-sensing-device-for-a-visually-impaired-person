#define ButtonReset  // the number of the pushbutton pin
#define ButtonHold
#define ButtonCali

short int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  pinMode(ButtonReset, INPUT);
  pinMode(ButtonHold, INPUT);
  pinMode(ButtonCali, INPUT);
}

void loop() {
  buttonState = digitalRead(ButtonReset); // read the state of the pushbutton value:
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }
}

void BReset(){
  buttonState = digitalRead(ButtonReset); // read the state of the pushbutton value:
  if (buttonState == HIGH) {
    Red=0, Green=0, Blue=0;
    strColor=String("Unknown");
  } 
  else {
    continue;
  }
}

void BHold(){
  buttonState = digitalRead(ButtonHold); // read the state of the pushbutton value:
  if (buttonState == HIGH) {
    digitalWrite(MotorPinR, LOW);

    digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
    digitalWrite(s3,LOW);

    //Serial.print("Red value= "); 
    GetData();                 //Executing GetData function to get the value
    data = map(data, 195, 0, 0, 255);
    percentageRGB();
    Red=data;
    strRed=String(Red);

    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);

    //Serial.print("Green value= ");
    GetData();
    data = map(data, 200, 0, 0, 255);
    percentageRGB();
    Green=data;  
    strGreen=String(Green);

    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);

    //Serial.print("Blue value= ");
    GetData();
    data = map(data, 150, 0, 0, 255);
    percentageRGB();
    Blue=data;
    strBlue=String(Blue);

    //Serial.println();
    //delay(2000);

    getColor();

    ToDisplay();
  } 
  else {
    VibrationMo();
  }
}

void BCali(){
  buttonState = digitalRead(ButtonReset); // read the state of the pushbutton value:
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }
}