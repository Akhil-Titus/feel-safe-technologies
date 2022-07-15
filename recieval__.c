#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3

const String Employee_ = "+919207807971";
SoftwareSerial gsm(rxPin,txPin);



String smsStatus,senderNumber,receivedDate,msg;

int buttonPin;
const int employee_pin = 7;     // the number of the pushbutton pin



void setup()
{
gsm.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
delay(100);
pinMode(employee_pin, INPUT);
}





long get_otp()   //otp generator
{
  
  Serial.println("\n Generating OTP");
  long randnum;
  randnum = random(100000,999999);
  //Serial.println(randnum);
  return randnum;
  
}
int rand_otp = int(randnum);
/*
void encryption_(long randnum)
{
    Serial.println(randnum);
    Serial.println("works with me");
    char c;
    //printf("Enter a character: ");
    //scanf("%c", &c);  

    // %d displays the integer value of a character
    // %c displays the actual character
    //printf("ASCII value of %c = %d", c, c);
    int otp1[6];
    
    
    for (int j = 0; j < 6; j++)
      {
        printf ("Enter otp %d:", j);
        scanf ("%d", &otp1[j]);
      }
    int algo[6] = { 67, 38, 97, 50 ,32 , 69};
    for (int i = 0; i < 6; i++)
      {
        printf ("%c", algo[i]);
      }
    int algo2[6] = { 35, 36, 37, 38 , 40, 39};
    int algo3[6] = { 40, 39, 37, 35, 38, 36 };
    int algo4[6] = { 38, 37, 36, 35, 37, 34 };
    int otp2[6];
    for (int k = 0; k < 6; k++)
      {
        otp2[k] = otp1[k] + algo[k];
        //printf("%d",otp2[k]);
        printf ("%c%c%c%c%c%c", otp2[k], algo3[k], algo[k], algo2[k], otp2[k],
          algo4[k]);

      }
    
    


}  */

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
    encryption_(randnum);
    Serial.println("Recieving.......");
    
    
  }
//  break;

  if (gsm.available()>0)
  Serial.write(gsm.read());
  recvd_sms = gsm.read();
  
  dummy_1 = parser_(recvd_sms);
}

char recvd_sms;

char parser_(char recvd_sms)
  {
    Serial.print(recvd_sms);
    Serial.println("it lives v2.0");
  }