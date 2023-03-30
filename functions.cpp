#include "functions.h"
#include "DFRobot_SIM808.h"


extern DFRobot_SIM808 sim808;

void send_sms(String message, int8_t idx_start, int8_t idx){
  char phone_number_arr[PHONE_NUMBER_LENGTH] = {0};
  char sms_arr[MESSAGE_LENGTH] = {0};
  idx = message.indexOf(F("|"), idx_start);
  
  if(idx == -1){
    #if defined(DEBUG)
    Serial.println(F("Error, phone number not found"));
    #endif
    return;
  }
  
  String phone_number = message.substring(idx_start, idx); 

//  #if defined(DEBUG)
//  Serial.print(F("Phone number: "));
//  Serial.println(phone_number);
//  #endif

  idx_start = idx + 1;
  idx = message.indexOf(F("|"), idx_start);
  
  if(idx == -1){
    #if defined(DEBUG)
    Serial.println(F("Error, sms content not found"));
    #endif
    return;
  }
  
  String sms = message.substring(idx_start, idx); 
//
//  #if defined(DEBUG)
//  Serial.print(F("SMS: "));
//  Serial.println(sms);
//  #endif

  phone_number.getBytes(phone_number_arr, PHONE_NUMBER_LENGTH);
  sms.getBytes(sms_arr, MESSAGE_LENGTH);

  sim808.sendSMS(phone_number_arr, sms_arr);
  Serial.print(F("SMS sent "));
  Serial.print(phone_number_arr);
  Serial.print(F(" "));
  Serial.println(sms_arr);
}

void parse_command(String message){
  int8_t idx_start, idx = 0;

  idx = message.indexOf(F("|"), idx_start);
  if(idx == -1) return;

  uint8_t command = message.substring(idx_start, idx).toInt();


  if(command == 1){ // send sms
//    #if defined(DEBUG)
//    Serial.println(F("command == 1"));
//    #endif
    idx_start = idx + 1;
    send_sms(message, idx_start, idx);
  };
  
}
