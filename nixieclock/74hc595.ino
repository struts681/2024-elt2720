#include "74hc595.h"

void sr_init() {
  pinMode(SR_DATA, OUTPUT);
  pinMode(SR_CLK, OUTPUT);
  pinMode(SR_LATCH, OUTPUT);
}

void sr_set(uint16_t _srreg) {
  bool _bit;
  for(int _i = 0; _i < 16; _i++) {
    _bit = ((_srreg >> _i) & _SRMASK);
    digitalWrite(SR_DATA, _bit);
    digitalWrite(SR_CLK, HIGH);
    digitalWrite(SR_CLK, LOW);
  }
  digitalWrite(SR_DATA, LOW);
  digitalWrite(SR_LATCH, HIGH);
  digitalWrite(SR_LATCH, LOW);
  return;
}