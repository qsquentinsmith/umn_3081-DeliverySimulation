#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
//#include "battery.h"

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

    Battery battery_init = Battery(5000);
    ASSERT_EQ(battery_init.GetChargeRemaining(), 5000) << "Battery(5000), should be 5000"; 
  }


  TEST_F(BatteryTest, BatteryLevels) {
    Battery battery = Battery(); 
    ASSERT_EQ(battery.GetChargeRemaining(), 10000); 
    ASSERT_EQ(battery.IsDead(), false) << "Check isDead when has charge";

    battery.DrainBattery(500); 
    ASSERT_EQ(battery.GetChargeRemaining(), 9500) << "Checking battery drain of 500";

    battery.DrainBattery(9500); 
    ASSERT_EQ(battery.GetChargeRemaining(), 0);
    ASSERT_EQ(battery.IsDead(), true);

  }
}  // namespace csci3081