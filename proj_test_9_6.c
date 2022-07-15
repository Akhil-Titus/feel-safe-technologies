#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3

const String Employee_ = "+919207807971";
SoftwareSerial gsm(rxPin,txPin);



String smsStatus,senderNumber,receivedDate,msg;

int buttonPin;
const int employee_pin = 7;     // the number of the pushbutton pin
int buttonState = 0;


void setup()
{
gsm.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
delay(100);
randomSeed(analogRead(0));
pinMode(employee_pin, INPUT);
}



void SendSMS(long randnum) // <-- pass randnum as argument to function 
{
   Serial.println("\n Sending SMS");    
   Serial.println(randnum); // <-- use f inside function2
   gsm.println("AT+CMGF=1");
   delay(1000);
   gsm.println("AT+CMGS=\""+Employee_+"\"\r"); //replace x by your number "AT+CMGS=\"+919207807971\"\r"
   delay(1000);
   gsm.println(randnum);
   delay(100);
   gsm.println((char)26);
   delay(1000);
}

long get_otp()   //otp generator
{
  
  Serial.println("\n Generating OTP");
  long randnum;
  randnum = random(10000,99999);
  Serial.println(randnum);
  return randnum;
  
}

void RecieveMessage()
{
gsm.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
gsm.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
delay(1000);
}

void loop()
{
   while(digitalRead(employee_pin)==HIGH)
  {
    RecieveMessage();
    long randnum = get_otp();  // <-- store value returned by function1 in f 
    delay(2000);
    SendSMS(randnum);
    Serial.println("Recieving.......");
    
    
  }
//  break;

  if (gsm.available()>0)
  Serial.write(gsm.read());
}
