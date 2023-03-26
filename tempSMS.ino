#include <SoftwareSerial.h>
#define LIMIT 39 // Change it to your favoured value in Celsius.
#define LIMIT2 42
#define LIMIT3 45
int value;
int tempPin = A1;
SoftwareSerial GSMSerial(9, 10);//Connect 9 to TX of GSM and 10 to RX of GSM

void setup() {
  // Setting up the Arduino.
  analogReference(tempPin);
  pinMode(tempPin,INPUT); //Setting up the temperature pin as an input pin
  GSMSerial.begin(19200);   // Setting the baud rate of GSM Module  
  Serial.begin(19200);    // Setting the baud rate of Serial Monitor (Arduino)
}

void loop() {
  // Arduino does this forever.
  value = analogRead(tempPin);
  float mv = (value/1024.0)*5000; 
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  Serial.print("Temperature is :");
  Serial.print(cel);
  Serial.println("*C");
  if(cel>LIMIT){
    initialOverheating();
    while(1);

  } else if(cel>LIMIT2) {
    mainOverheating();
    while(1);

  } else if(el>LIMIT3) {
    severeOverheating();
    while(1);
  }

}

void initialOverheating(){
  GSMSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  GSMSerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  GSMSerial.println("ALERT: Your dog is overheating. Recorded temperature:" + cel + ". This is not life threatening, but the dog should not remain at this temperature.");// The SMS text you want to send
  delay(100);
  GSMSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void mainOverheating(){
  GSMSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  GSMSerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  GSMSerial.println("Temperature exceeded the set value!");// The SMS text you want to send
  delay(100);
  GSMSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void severeOverheating(){
  GSMSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  GSMSerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  GSMSerial.println("Temperature exceeded the set value!");// The SMS text you want to send
  delay(100);
  GSMSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
