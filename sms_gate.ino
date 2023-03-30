#include "DFRobot_SIM808.h"
#include "functions.h"


#define SIM_PIN_TX    2
#define SIM_PIN_RX    3

char gprsBuffer[32];

SoftwareSerial mySerial(SIM_PIN_TX, SIM_PIN_RX);
DFRobot_SIM808 sim808(&mySerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init()) 
  { 
      delay(1000);
      #if defined(DEBUG)
      Serial.println(F("Sim808 init error"));
      #endif
  }

  if(sim808.enableCLIPring())
  {
    #if defined(DEBUG)
    Serial.println(F("CLIP Enabled"));
    #endif
  }
  else
  {
    #if defined(DEBUG)
    Serial.println(F("CLIP ERROR"));
    #endif
  }

//  for(uint8_t i=0; i<255; i++){
//    sim808.deleteSMS(i);
//    Serial.print(F("Delete message: "));
//    Serial.println(i);
//  }

}

void serialEvent() {
  //statements
  String message = Serial.readString();
  message.trim();
//  Serial.println(message);
  parse_command(message);
}

void loop() {
  // put your main code here, to run repeatedly:

   if(sim808.readable())
   {
      char *s = NULL;
      sim808_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);

//      #if defined(DEBUG)
//      Serial.println(F("SMS"));
//      #endif
      if(NULL != (s = strstr(gprsBuffer,"+CMTI: \"SM\""))) 
      { 
        char message[MESSAGE_LENGTH];
        int messageIndex = atoi(s+12);
        char phone_number_arr[PHONE_NUMBER_LENGTH] = {0};
        char datetime[24] = {0};
        sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone_number_arr, datetime);
        sim808.deleteSMS(messageIndex);

        Serial.print(F("Phone|"));
        Serial.println(phone_number_arr);
        
        Serial.print(F("SMS|"));
        Serial.println(message);
      }

     sim808_clean_buffer(gprsBuffer, 32);  
   }

}
