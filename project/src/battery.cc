#include "battery.h"

namespace csci3081 {

   Battery::Battery(float maxCharge) {

    if (maxCharge < 0){
      charge_remaining_ = 0;
      max_charge_ = 0;
    }
    else{
      charge_remaining_ = maxCharge; 
      max_charge_ = maxCharge;
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