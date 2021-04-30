#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "robot.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class RobotTest : public ::testing::Test {
    protected:
      Robot* robot;
      picojson::object obj;
      
      virtual void SetUp() {

        //robot setup 
        obj = JsonHelper::CreateJsonObject();
        JsonHelper::AddStringToJsonObject(obj, "type", "robot");
        std::vector<float> positionToAdd;
        positionToAdd.push_back(498.292);
        positionToAdd.push_back(253.883);
        positionToAdd.push_back(-228.623);
        JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);
        std::vector<float> directionToAdd;
        directionToAdd.push_back(1);
        directionToAdd.push_back(0);
        directionToAdd.push_back(0);
        JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", directionToAdd);
        JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
        JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
        robot = new Robot(positionToAdd, directionToAdd, obj); 
      }
    
      virtual void TearDown() {
        delete robot;
      }

  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(RobotTest, RobotConstructor) {
    /*** Robot(): Constructor Check ***/
    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj).serialize());
  }


  TEST_F(RobotTest, GetPositionTest) {
    /*** GetPosition() ***/
    ASSERT_FLOAT_EQ(robot->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(robot->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(robot->GetPosition()[2], -228.623);
  }


  TEST_F(RobotTest, GetDirectionTest) {
    /*** GetDirection() ***/
    ASSERT_FLOAT_EQ(robot->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[2], 0.0);
  }


  TEST_F(RobotTest, TestCarrierFunctions) {
    /*** SetStrategy(): If compiling and running then it is run correctly. Need Carrier get strategy to test ***/ 
    robot->SetStrategy();
  }
  
  /*** 
    Public Function not used are:
      - GetRoute: smart path relies on other classes. Would be tested in stategy_test 
  ***/


}  // namespace csci3081