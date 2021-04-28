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
    return dead_battery_;
  }

  float Battery::GetChargeRemaining() {
    return charge_remaining_; 
  }

  void Battery::DrainBattery(float dt) {
    charge_remaining_ -= dt;
    if (charge_remaining_ <= 0 ){
      charge_remaining_ = 0;
      dead_battery_ = true;
    }
  } 

} //csci3081