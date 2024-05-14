#include "ds3231.h"

void ds3231_begin() {
  Wire.begin(_rtc);
}

uint8_t rtc_get_byte(uint8_t _rtc_reg) {

  Wire.beginTransmission(_rtc); //open the line to the rtc
  Wire.write(_rtc_reg); //set the address pointer to the register to read
  Wire.endTransmission();
  Wire.requestFrom(_rtc, 1); //get one byte from the rtc
  byte _buf = Wire.read(); //read it to a buffer
  return _buf; //return the value - this works fine with minutes and seconds but not necessarily hours

}

uint8_t rtc_get_mins() {
  Wire.beginTransmission(_rtc);
  Wire.write(rtc_minutes);
  Wire.endTransmission();
  Wire.requestFrom(_rtc, 1);
  byte _buf = Wire.read();
  return _buf;
}

uint8_t rtc_get_hours() {

  Wire.beginTransmission(_rtc);
  Wire.write(rtc_hours);
  Wire.endTransmission();
  Wire.requestFrom(_rtc, 1);
  byte _buf = Wire.read();

  _buf &= 0x3F;  //mask with 0011 1111 to ignore the value of bits 7 and

  return _buf;

}

void rtc_set_mins(uint8_t _dec_minutes) {
  
  Wire.beginTransmission(_rtc); //open the line
  Wire.write(rtc_minutes); //select the register
  Wire.write(dec_to_bcd(_dec_minutes)); //write the value
  Wire.endTransmission(); 

  rtc_set_secs(0);
  
}

void rtc_set_hrs(uint8_t _dec_hours) {

  Wire.beginTransmission(_rtc); //open the line
  Wire.write(rtc_hours); //select the register
  Wire.write(dec_to_bcd(_dec_hours) & 0b00111111); //write the value
  Wire.endTransmission(); //close the line!

}

void rtc_set_secs(uint8_t _secs) {

  Wire.beginTransmission(_rtc); //open the line
  Wire.write(rtc_seconds); //select the register
  Wire.write(dec_to_bcd(_secs)); //write the value
  Wire.endTransmission(); //close the line

}

uint8_t bcd_to_dec(uint8_t _bcd) {
  return ((_bcd/16*10) + (_bcd%16));
}

uint8_t dec_to_bcd(uint8_t _dec) {
  return ((_dec/10*16) + (_dec%10));
}
