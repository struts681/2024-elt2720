/*
   Nixie Tube Clock Project
   For Pro Mini ATMega328p
   VTSU Spring 2024
   ELT-2720
   Amelia Vlahogiannis
*/

#include "ds3231.h"
#include "74hc595.h"
#include <stdint.h>

#define LATCH 8
#define DATA 11
#define SRCLK 12

#define HV_SHDN 9

#define HHPB 3
#define MMPB 4
#define ONPB 5

uint16_t hh;
uint16_t hh_dec;
uint8_t mm;
uint8_t mm_dec;
uint16_t hhmm;

bool hr_change = 0;

uint64_t ontime;

void setup() {

  Serial.begin(9600);
  sr_init();

  pinMode(HV_SHDN, OUTPUT);
  pinMode(HHPB, INPUT_PULLUP);
  pinMode(MMPB, INPUT_PULLUP);
  pinMode(ONPB, INPUT_PULLUP);
}



void loop() {
  if (mm != rtc_get_mins() || hr_change) {
    hh = rtc_get_hours();
    hh_dec = bcd_to_dec(hh);
    mm = rtc_get_mins();
    mm_dec = bcd_to_dec(mm);
    mm &= 0x00FF;

    hh <<= 8;
    hhmm = hh & 0xFF00;
    hhmm += mm;

    sr_set(hhmm);
    digitalWrite(HV_SHDN, LOW);
    hr_change = 0;
    ontime = millis();
  }
  //this ends the bit of the code that does the time
  
  if (!digitalRead(HHPB)) {
    if (hh_dec == 23) { //wrap around
      rtc_set_hrs(0);
    }
    else {
      rtc_set_hrs(hh_dec + 1); //increment the hours by one
    }
    hr_change = 1;
    digitalWrite(HV_SHDN, LOW);
    ontime = millis(); //on!
    delay(300); //debounce
  }

  if(!digitalRead(MMPB)) {
    if (mm_dec == 59) {
      rtc_set_mins(0);
    }
    else {
      rtc_set_mins(mm_dec + 1);
    }
    digitalWrite(HV_SHDN, LOW);
    ontime = millis();  
    delay(300);
  }

  if(!digitalRead(ONPB)) {
    digitalWrite(HV_SHDN, LOW);
    ontime = millis();  
    delay(100);
  }

  if ((millis() - ontime) > 10000) digitalWrite(HV_SHDN, HIGH);
}
