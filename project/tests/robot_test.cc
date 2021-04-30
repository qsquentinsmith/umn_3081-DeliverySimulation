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
  //Testing robot constructor
  TEST_F(RobotTest, RobotConstructor) {
    
    //testing values set in constructor
    ASSERT_FLOAT_EQ(robot->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(robot->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(robot->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(robot->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[2], 0.0);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(RobotTest, TestCarrierFunctions) {
    
    // Test Speed
    ASSERT_EQ(robot-> GetSpeed(), 30) << "get speed";
    robot->SetSpeed(40);
    ASSERT_EQ(robot-> GetSpeed(), 40) << "new speed";
    
    ASSERT_EQ(robot->IsScheduled(), false) << "isscheduled";
    robot->SetScheduled(true);
    ASSERT_EQ(robot->IsScheduled(), true) << "isscheduled";


    ASSERT_NE(robot->GetBattery(), nullptr) << "getbattery";


    ASSERT_EQ(robot->ReachedNextPosition(robot->GetPosition(), 1), true) << "reached next position";

    std::vector<float> source;
    source.push_back(1);
    source.push_back(0);
    source.push_back(0);
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    Vector3D newdir1 = robot->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    ASSERT_FLOAT_EQ(newdir[0], -0.82369328) << "GetNewDirection x test";
    ASSERT_FLOAT_EQ(newdir[1], -0.4213683) << "GetNewDirection y test";
    ASSERT_FLOAT_EQ(newdir[2], 0.37944442) << "GetNewDirection z test";

    Vector3D newpos1 = robot->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    ASSERT_FLOAT_EQ(newpos[0], 168.8147) << "getnewposition x test";
    ASSERT_FLOAT_EQ(newpos[1], 85.335663) << "getnewposition y test";
    ASSERT_FLOAT_EQ(newpos[2], -76.84523) << "getnewposition z test";
   
  }


}  // namespace csci3081