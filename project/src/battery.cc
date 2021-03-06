#include "battery.h"

namespace csci3081 {

   Battery::Battery(float maxCharge) {

    if (maxCharge < 0){
      chargeRemaining = 0;
      this->maxCharge = 0;
    }
    else{
      chargeRemaining = maxCharge; 
      this->maxCharge = maxCharge;
    }
  }

  bool Battery::IsDead() {
    return deadBattery;
  }

  float Battery::GetChargeRemaining() {
    return chargeRemaining; 
  }

  void Battery::DrainBattery(float dt) {
    chargeRemaining -= dt;
    if (chargeRemaining <= 0 ){
      chargeRemaining = 0;
      deadBattery = true;
    }
  } 

} //csci3081
