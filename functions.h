#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

#define DEBUG

#define MESSAGE_LENGTH 50
#define PHONE_NUMBER_LENGTH 15

void send_sms(String message, int8_t idx_start, int8_t idx);
void parse_command(String message);

#endif
