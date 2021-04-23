#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
//#include "drone.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class CarrierTest : public ::testing::Test {
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
    drone = new Drone(position_to_add, direction_to_add, obj); 
    }
    virtual void TearDown() {
      delete drone;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing drone constructor
  TEST_F(CarrierTest, DroneConstructor) {
    //testing values set in constructor
    ASSERT_FLOAT_EQ(drone->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(drone->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(drone->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(drone->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[2], 0.0);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(CarrierTest, TestCarrierFunctions) {
    
    // Test Speed
    ASSERT_EQ(drone-> GetSpeed(), 30) << "get speed";
    drone->SetSpeed(40);
    ASSERT_EQ(drone-> GetSpeed(), 40) << "new speed";
    
    ASSERT_EQ(drone->IsScheduled(), false) << "isscheduled";
    drone->SetScheduled(true);
    ASSERT_EQ(drone->IsScheduled(), true) << "isscheduled";


    ASSERT_NE(drone->GetBattery(), nullptr) << "getbattery";


    ASSERT_EQ(drone->ReachedNextPosition(drone->GetPosition(), 1), true) << "reached next position";

    std::vector<float> source;
    source.push_back(1);
    source.push_back(0);
    source.push_back(0);
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    Vector3D newdir1 = drone->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    ASSERT_FLOAT_EQ(newdir[0], -0.82369328) << "GetNewDirection x test";
    ASSERT_FLOAT_EQ(newdir[1], -0.4213683) << "GetNewDirection y test";
    ASSERT_FLOAT_EQ(newdir[2], 0.37944442) << "GetNewDirection z test";

    Vector3D newpos1 = drone->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    ASSERT_FLOAT_EQ(newpos[0], 168.8147) << "getnewposition x test";
    ASSERT_FLOAT_EQ(newpos[1], 85.335663) << "getnewposition y test";
    ASSERT_FLOAT_EQ(newpos[2], -76.84523) << "getnewposition z test";
   
  }


}  // namespace csci3081