#include "MechanicalEncoder.h"
#include <Arduino.h>

static MechanicalEncoder* encoderInstance = nullptr;

MechanicalEncoder::MechanicalEncoder(uint8_t _dt, uint8_t _clk, int _min, int _max, int _actual, bool _loop) {   
   
    pinDT = _dt;
    pinCLK = _clk;

    state = 0;
    value_reported = value = _actual;

    min = _min;
    max = _max;
    loop = _loop;
    
    pinMode(pinDT, INPUT);
    pinMode(pinCLK, INPUT);
    //pinMode(pinDT, INPUT_PULLUP);
    //pinMode(pinCLK, INPUT_PULLUP);
}

void MechanicalEncoder::AttachInterrupts()
{
    attachInterrupt(pinDT, HandleInterrupt, CHANGE);
    attachInterrupt(pinCLK, HandleInterrupt, CHANGE);

    encoderInstance = this;
} 

void IRAM_ATTR MechanicalEncoder::HandleInterrupt() {
    if (encoderInstance) encoderInstance->Process();
}

void IRAM_ATTR MechanicalEncoder::Process() {
    
  unsigned char pinstate = (digitalRead(pinCLK) << 1) | digitalRead(pinDT);
  state = stateTable[state & 0xf][pinstate];
  unsigned char result = state & 48;

  // CW rotation
  if(result == 16){
    if(value >= max) {
        if (loop) value = min;
    }
    else value++;
  }
  // CCW rotation
  else if(result == 32){
    if(value <= min) {
        if (loop) value = max;
    }
    else value--;
  }
};

bool MechanicalEncoder::Updated() {
    if (value != value_reported) {
        value_reported = value;
        return true;
    }
    return false;
};

int MechanicalEncoder::Value() {
	return value;
};

bool MechanicalEncoder::ProcessAndCheck() {
    Process();
    return Updated();
};