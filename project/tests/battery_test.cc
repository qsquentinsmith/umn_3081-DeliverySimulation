#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class BatteryTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

  TEST_F(BatteryTest, BatteryConstructor) {
    Battery battery = Battery(); 
    ASSERT_EQ(battery.GetChargeRemaining(), 10000) << "Battery (), should be 10000"; 

    Battery batteryInit = Battery(5000);
    ASSERT_EQ(batteryInit.GetChargeRemaining(), 5000) << "Battery(5000), should be 5000"; 
    
     /***** edge case initiation: intiate with negative number ***/
    Battery batteryInit2 = Battery(-5000);
    ASSERT_EQ(batteryInit2.GetChargeRemaining(), 0) << "Edge Case: Battery(-5000), should be 0"; 
  }


  TEST_F(BatteryTest, BatteryLevels) {
    Battery battery = Battery(); 
    ASSERT_EQ(battery.GetChargeRemaining(), 10000); 
    ASSERT_EQ(battery.IsDead(), false) << "Check isDead when has charge";

    battery.DrainBattery(500); 
    ASSERT_EQ(battery.GetChargeRemaining(), 9500) << "Checking battery drain of 500";

    battery.DrainBattery(9500); 
    ASSERT_EQ(battery.GetChargeRemaining(), 0) << "Checking battery when no charge";
    ASSERT_EQ(battery.IsDead(), true) << "Check isDead when has no charge";

    /**** edge case 1: try to drain below zero ***/
    battery.DrainBattery(500);
    ASSERT_EQ(battery.GetChargeRemaining(), 0) << "Edge Case: Drain below zero";
    ASSERT_EQ(battery.IsDead(), true) << "Edge Case: Drain below zero";

    /*** edge case 2: drain battery negative number ***/
    battery.DrainBattery(-500);
    ASSERT_EQ(battery.GetChargeRemaining(), 500) << "Edge Case 2: Drain battery negative number";

    // flag already switched to dead (will implement flag switching when recharge feature added)
    ASSERT_EQ(battery.IsDead(), true) << "Edge Case 2: drain battery negative number";
  }


}  // namespace csci3081