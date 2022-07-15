#include <SoftwareSerial.h>

//sender phone number with country code
const String PHONE = "+919207807971";

//GSM Module RX pin to Arduino 3
//GSM Module TX pin to Arduino 2
#define rxPin 2
#define txPin 3
SoftwareSerial gsm(rxPin,txPin);

#define RELAY_1 7
#define RELAY_2 8

String smsStatus,senderNumber,receivedDate,msg;
boolean isReply = false;

void setup() {

  Serial.begin(9600);
  Serial.println("Arduino serial initialize");

  gsm.begin(9600);
  Serial.println("gsmL software serial initialize");

  smsStatus = "";
  senderNumber="";
  receivedDate="";
  msg="";

  gsm.print("AT+CMGF=1\r"); //SMS text mode
  delay(1000);
  //delete all sms
  gsm.println("AT+CMGD=1,4");
  delay(1000);
  //gsm.println("AT+CMGDA= \"DEL ALL\"");
  //delay(1000);
}

void loop() {
//////////////////////////////////////////////////
while(gsm.available()){
  parseData(gsm.readString());
}
//////////////////////////////////////////////////
while(Serial.available())  {
  gsm.println(Serial.readString());
}
//////////////////////////////////////////////////
} //main loop ends

//***************************************************
void parseData(String buff){
  Serial.println(buff);

  unsigned int len, index;
  //////////////////////////////////////////////////
  //Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index+2);
  buff.trim();
  //////////////////////////////////////////////////

  //////////////////////////////////////////////////
  if(buff != "OK"){
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();

    buff.remove(0, index+2);

    if(cmd == "+CMTI"){
      //get newly arrived memory location and store it in temp
      index = buff.indexOf(",");
      String temp = buff.substring(index+1, buff.length());
      temp = "AT+CMGR=" + temp + "\r";
      //get the message stored at memory location "temp"
      gsm.println(temp);
    }
    else if(cmd == "+CMGR"){
      extractSms(buff);

      if(senderNumber == PHONE){
        doAction();
        //delete all sms
        gsm.println("AT+CMGD=1,4");
        delay(1000);
        gsm.println("AT+CMGDA= \"DEL ALL\"");
        delay(1000);
      }
    }
  //////////////////////////////////////////////////
  }
  else{
  //The result of AT Command is "OK"
  }
}

//************************************************************
void extractSms(String buff){
   unsigned int index;

    index = buff.indexOf(",");
    smsStatus = buff.substring(1, index-1);
    buff.remove(0, index+2);

    senderNumber = buff.substring(0, 13);
    buff.remove(0,19);

    receivedDate = buff.substring(0, 20);
    buff.remove(0,buff.indexOf("\r"));
    buff.trim();

    index =buff.indexOf("\n\r");
    buff = buff.substring(0, index);
    buff.trim();
    msg = buff;
    buff = "";
    msg.toLowerCase();
}

void doAction(){
  if(msg == "1234"){
    //digitalWrite(RELAY_1, HIGH);
    Serial.println("it works");
    //Reply("Relay 1 has been OFF");
  }


  smsStatus = "";
  senderNumber="";
  receivedDate="";
  msg="";
}
/*
void Reply(String text)
{
    gsm.print("AT+CMGF=1\r");
    delay(1000);
    gsm.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    gsm.print(text);
    delay(100);
    gsm.write(0x1A); //ascii code for ctrl-26 //gsm.println((char)26); //ascii code for ctrl-26
    delay(1000);
    Serial.println("SMS Sent Successfully.");
}
*/
