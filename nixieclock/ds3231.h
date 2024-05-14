#ifndef RTC_DS3231
#define RTC_DS3231

#include <stdint.h>
#include <Wire.h>

enum rtc_regs {
  rtc_seconds = 0x00, //reg is already bcd!
  rtc_minutes = 0x01, //reg is also already bcd!
  rtc_hours   = 0x02, //this one is more annoying
  rtc_weekday = 0x03, //1-7
  rtc_date    = 0x04, //bcd
  rtc_month   = 0x05, //bcd but the msb is the century
  rtc_year    = 0x06, //bcd again! (2 digits because we know the century is 20 or 21)
  rtc_a1_secs = 0x07, //alarm 1 seconds
  rtc_a1_mins = 0x08, //and so on
  rtc_a1_hrs  = 0x09, //
  rtc_a1_date = 0x0A, //
  rtc_a2_mins = 0x0B, // alarm 2 minutes (doesnt have seconds)
  rtc_a2_hrs  = 0x0C, // and so on
  rtc_a2_date = 0x0D, //
  rtc_ctrl    = 0x0E, //we dont really need to mess with this
  rtc_status  = 0x0F, //or this
  rtc_ofs     = 0x10, //or this
  rtc_temp1   = 0x11, //self-explanatory i hope
  rtc_temp2   = 0x12,
  _rtc        = 0x68, //i2c address of the device
  read_length =    1, //all the registers are 8 bits
};

void ds3231_begin(); //init the device, wire and everything
uint8_t rtc_get_byte(uint8_t _rtc_reg); //read a byte
uint8_t rtc_get_hours(); //read and understand the hours byte specifically
void rtc_set_mins(uint8_t _dec_minutes); //set minutes
void rtc_set_hrs(uint8_t _hours); //set hours
void rtc_set_secs(uint8_t _secs); //set seconds

#endif
