#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
//#include "drone.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class DroneTest : public ::testing::Test {
   protected:
    Drone* drone;
    picojson::object obj;

    virtual void SetUp() {
      //drone setup 
      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "drone");
      std::vector<float> position_to_add;
      position_to_add.push_back(498.292);
      position_to_add.push_back(253.883);
      position_to_add.push_back(-228.623);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
      std::vector<float> direction_to_add;
      direction_to_add.push_back(1);
      direction_to_add.push_back(0);
      direction_to_add.push_back(0);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
      JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      JsonHelper::AddStringToJsonObject(obj, "path", "beeline");

      drone = new Drone(position_to_add, direction_to_add, obj); 
    }
    virtual void TearDown() {
      delete drone;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(DroneTest, DroneConstructor) {
    /*** Drone(): Constructor Check ***/
    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(DroneTest, GetPositionTest) {
    /*** GetPosition() ***/
    ASSERT_FLOAT_EQ(drone->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(drone->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(drone->GetPosition()[2], -228.623);
  }

  TEST_F(DroneTest, GetDirectionTest) {
    /*** GetDirection() ***/
    ASSERT_FLOAT_EQ(drone->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[2], 0.0);
  }

  TEST_F(DroneTest, TestDroneFunctions) {
    /*** SetStrategy(): If compiling and running then it is run correctly. Need Carrier get strategy to test ***/ 
    drone->SetStrategy();
  }
    
    
    /*** 
      Public Functions not tested are:
      - GetRoute(): this is tested in strategy_test 
    ***/


}  // namespace csci3081