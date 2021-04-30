#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "entity_base.h"
//#include "drone.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class CarrierTest : public ::testing::Test {
   protected:
    Drone* drone;
    picojson::object obj;

    Robot* robot;
    picojson::object obj_r;
    
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    
    virtual void SetUp() {

      //drone setup 
      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "drone");
      
      position_to_add.push_back(498.292);
      position_to_add.push_back(253.883);
      position_to_add.push_back(-228.623);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
      
      direction_to_add.push_back(1);
      direction_to_add.push_back(0);
      direction_to_add.push_back(0);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
      JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      JsonHelper::AddStringToJsonObject(obj, "path", "smart");
      drone = new Drone(position_to_add, direction_to_add, obj); 

      //drone setup 
      obj_r = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj_r, "type", "robot");
      JsonHelper::AddStdFloatVectorToJsonObject(obj_r, "position", position_to_add);
      JsonHelper::AddStdFloatVectorToJsonObject(obj_r, "direction", direction_to_add);
      JsonHelper::AddFloatToJsonObject(obj_r, "speed", 30.0);
      JsonHelper::AddFloatToJsonObject(obj_r, "radius", 1.0);
      JsonHelper::AddStringToJsonObject(obj_r, "path", "smart");
      robot = new Robot(position_to_add, direction_to_add, obj_r); 

    }
    virtual void TearDown() {
      delete drone;
      delete robot;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

  /**************************** DRONE TESTS ***********************************/
  TEST_F(CarrierTest, DroneConstructor) {
    
    ASSERT_FLOAT_EQ(drone->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(drone->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(drone->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(drone->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(drone->GetDirection()[2], 0.0);

    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());

  }


  TEST_F(CarrierTest, DroneSpeedTest) {
    /*** GetSpeed(), SetSpeed() ***/
    ASSERT_EQ(drone-> GetSpeed(), 30) << "get speed";
    drone->SetSpeed(40);
    ASSERT_EQ(drone-> GetSpeed(), 40) << "new speed";
  }


  TEST_F(CarrierTest, DroneIDTest) {
    drone-> SetId(30);
    ASSERT_EQ(drone-> GetId(), 30);
    drone-> SetId(40);
    ASSERT_EQ(drone-> GetId(), 40);
  }


  TEST_F(CarrierTest, DroneDetailsTest) {
    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());
  }


  TEST_F(CarrierTest, DroneRadiusTest) {
    ASSERT_EQ(drone->GetRadius(), 1.0);
  }

  TEST_F(CarrierTest, DroneNameTest) {
    ASSERT_EQ(drone->GetName(), "");
  }


  TEST_F(CarrierTest, DroneColorTest) {
    drone->SetColor("0xF7DC6F");
    ASSERT_NE(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());

    obj["color"] = picojson::value("0xF7DC6F");
    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());
  }


  TEST_F(CarrierTest, DroneScheduleTest) {
    /*** IsScheduled(), SetScheduled() ***/
    ASSERT_EQ(drone->IsScheduled(), false) << "isscheduled";
    drone->SetScheduled(true);
    ASSERT_EQ(drone->IsScheduled(), true) << "isscheduled";
  }


  TEST_F(CarrierTest, DroneVersionTest) {
    /*** GetVersion(), SetVersion() ***/
    drone->SetVersion(1);
    ASSERT_EQ(drone->GetVersion(), 1) << "version";
  }


  TEST_F(CarrierTest, DronePathTest) {
    /*** GetPath() ***/
    ASSERT_EQ(drone->GetPath(), "smart") << "get path";
  }


  TEST_F(CarrierTest, DroneBatteryTest) {
    /*** GetBattery() ***/
    ASSERT_NE(drone->GetBattery(), nullptr) << "getbattery";
  }


  TEST_F(CarrierTest, DroneDynamicTest) {
    /*** SetDynamic() ***/
    drone->SetDynamic(true);
    ASSERT_EQ(drone->IsDynamic(), true) << "isdynamic";
    drone->SetDynamic(false);
    ASSERT_EQ(drone->IsDynamic(), false) << "isdynamic";
  }


  TEST_F(CarrierTest, DroneReachNextPositionTest) {
    /*** ReachedNextPosition ***/
    ASSERT_EQ(drone->ReachedNextPosition(drone->GetPosition(), 1), true) << "reached next position";
  }


  TEST_F(CarrierTest, DronePositionDirectionTests) {
    // SetUp
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    /*** GetNewDirection(), SetDirection() ***/
    Vector3D newdir1 = drone->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    drone->SetDirection(newdir);
    ASSERT_FLOAT_EQ(drone->GetDirection()[0], -0.82369328);
    ASSERT_FLOAT_EQ(drone->GetDirection()[1], -0.4213683);
    ASSERT_FLOAT_EQ(drone->GetDirection()[2], 0.37944442);
    
    /*** GetNewPosition(), SetPosition() ***/
    Vector3D newpos1 = drone->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    
    drone->SetPosition(newpos);
    ASSERT_FLOAT_EQ(drone->GetPosition()[0], 251.18401);
    ASSERT_FLOAT_EQ(drone->GetPosition()[1], 127.4725);
    ASSERT_FLOAT_EQ(drone->GetPosition()[2], -114.78968);
  }


  TEST_F(CarrierTest, DroneRouteTest) {
    // SetUp
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);

    vector<float> newpos;
    newpos.push_back(168.8147);
    newpos.push_back(85.335663);
    newpos.push_back(-76.84523);

    /*** SetRoute(), GetRoute() ***/
    vector<vector<float>> route;
    route.push_back(target);
    route.push_back(newpos);
    drone->SetRoute(route);

    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][0], 2.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][1], 0.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][2], 0.0);

    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][0], 168.8147);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][1], 85.335663);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][2], -76.84523);
  }

  /**************************** ROBOT TESTS ***********************************/

  TEST_F(CarrierTest, RobotConstructor) {
    ASSERT_FLOAT_EQ(robot->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(robot->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(robot->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(robot->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(robot->GetDirection()[2], 0.0);

    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj_r).serialize());
  }


  TEST_F(CarrierTest, RobotSpeedTest) {
    /*** GetSpeed(), SetSpeed() ***/
    ASSERT_EQ(robot-> GetSpeed(), 30) << "get speed";
    robot->SetSpeed(40);
    ASSERT_EQ(robot-> GetSpeed(), 40) << "new speed";
  }


  TEST_F(CarrierTest, RobotDynamicTest) {
    /*** SetDynamic() ***/
    robot->SetDynamic(true);
    ASSERT_EQ(robot->IsDynamic(), true) << "isdynamic";
    robot->SetDynamic(false);
    ASSERT_EQ(robot->IsDynamic(), false) << "isdynamic";
  }


  TEST_F(CarrierTest, RobotIDTest) {
    robot-> SetId(30);
    ASSERT_EQ(robot-> GetId(), 30);
    robot-> SetId(40);
    ASSERT_EQ(robot-> GetId(), 40);
  }


  TEST_F(CarrierTest, RobotDetailsTest) {
    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj_r).serialize());
  }


  TEST_F(CarrierTest, RobotRadiusTest) {
    ASSERT_EQ(robot->GetRadius(), 1.0);
  }


  TEST_F(CarrierTest, RobotNameTest) {
    ASSERT_EQ(robot->GetName(), "");
  }


  TEST_F(CarrierTest, RobotColorTest) {
    robot->SetColor("0xF7DC6F");
    ASSERT_NE(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj).serialize());

    obj_r["color"] = picojson::value("0xF7DC6F");
    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj_r).serialize());
  }


  TEST_F(CarrierTest, RobotScheduleTest) {
    /*** IsScheduled(), SetScheduled() ***/
    ASSERT_EQ(robot->IsScheduled(), false) << "isscheduled";
    robot->SetScheduled(true);
    ASSERT_EQ(robot->IsScheduled(), true) << "isscheduled";
  }


  TEST_F(CarrierTest, RobotVersionTest) {
    /*** GetVersion(), SetVersion() ***/
    robot->SetVersion(1);
    ASSERT_EQ(robot->GetVersion(), 1) << "version";
  }


  TEST_F(CarrierTest, RobotPathTest) {
    /*** GetPath() ***/
    ASSERT_EQ(robot->GetPath(), "smart") << "get path";
  }


  TEST_F(CarrierTest, RobotBatteryTest) {
    /*** GetBattery() ***/
    ASSERT_NE(robot->GetBattery(), nullptr) << "getbattery";
  }


  TEST_F(CarrierTest, RobotReachNextPositionTest) {
    /*** ReachedNextPosition ***/
    ASSERT_EQ(robot->ReachedNextPosition(robot->GetPosition(), 1), true) << "reached next position";
  }


  TEST_F(CarrierTest, RobotPositionDirectionTests) {
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    /*** GetNewDirection(), SetDirection() ***/
    Vector3D newdir1 = robot->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    robot->SetDirection(newdir);
    ASSERT_FLOAT_EQ(robot->GetDirection()[0], -0.82369328);
    ASSERT_FLOAT_EQ(robot->GetDirection()[1], -0.4213683);
    ASSERT_FLOAT_EQ(robot->GetDirection()[2], 0.37944442);
    
    /*** GetNewPosition(), SetPosition() ***/
    Vector3D newpos1 = robot->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    
    robot->SetPosition(newpos);
    ASSERT_FLOAT_EQ(robot->GetPosition()[0], 251.18401);
    ASSERT_FLOAT_EQ(robot->GetPosition()[1], 127.4725);
    ASSERT_FLOAT_EQ(robot->GetPosition()[2], -114.78968);
  }


  TEST_F(CarrierTest, RobotRouteTest) {
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);

    vector<float> newpos;
    newpos.push_back(168.8147);
    newpos.push_back(85.335663);
    newpos.push_back(-76.84523);

    /*** SetRoute(), GetRoute() ***/
    vector<vector<float>> route;
    route.push_back(target);
    route.push_back(newpos);
    robot->SetRoute(route);

    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[0][0], 2.0);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[0][1], 0.0);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[0][2], 0.0);

    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[1][0], 168.8147);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[1][1], 85.335663);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetRoute()[1][2], -76.84523);
  }


        /***NOTE: Public Functions Not Included: 
    - Move() because of over reliance on other classes 
    - SetGraph() because of over reliance on other classes 
    - GetGraph() because of over reliance on other classes 
    ***/

}  // namespace csci3081