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

    Robot* robot;
    picojson::object obj_r;
    
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
  //Testing drone constructor
  TEST_F(CarrierTest, DroneConstructor) {
    //testing values set in constructor
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[2], 0.0);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(drone->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(CarrierTest, DroneSpeedTest) {
    /*** GetSpeed(), SetSpeed() ***/
    ASSERT_EQ(((Carrier*)drone)-> GetSpeed(), 30) << "get speed";
    ((Carrier*)drone)->SetSpeed(40);
    ASSERT_EQ(((Carrier*)drone)-> GetSpeed(), 40) << "new speed";
  }


  TEST_F(CarrierTest, DroneScheduleTest) {
    /*** IsScheduled(), SetScheduled() ***/
    ASSERT_EQ(((Carrier*)drone)->IsScheduled(), false) << "isscheduled";
    ((Carrier*)drone)->SetScheduled(true);
    ASSERT_EQ(((Carrier*)drone)->IsScheduled(), true) << "isscheduled";
  }


  TEST_F(CarrierTest, DroneVersionTest) {
    /*** GetVersion(), SetVersion() ***/
    ((Carrier*)drone)->SetVersion(1);
    ASSERT_EQ(((Carrier*)drone)->GetVersion(), 1) << "version";
  }


  TEST_F(CarrierTest, DronePathTest) {
    /*** GetPath() ***/
    ASSERT_EQ(((Carrier*)drone)->GetPath(), "smart") << "get path";
  }


  TEST_F(CarrierTest, DroneBatteryTest) {
    /*** GetBattery() ***/
    ASSERT_NE(((Carrier*)drone)->GetBattery(), nullptr) << "getbattery";
  }


  TEST_F(CarrierTest, DroneReachNextPositionTest) {
    /*** ReachedNextPosition ***/
    ASSERT_EQ(((Carrier*)drone)->ReachedNextPosition(((Carrier*)drone)->GetPosition(), 1), true) << "reached next position";
  }


  TEST_F(CarrierTest, DronePositionDirectionTests) {
    // SetUp
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    /*** GetNewDirection(), SetDirection() ***/
    Vector3D newdir1 = ((Carrier*)drone)->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    ((Carrier*)drone)->SetDirection(newdir);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[0], -0.82369328);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[1], -0.4213683);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetDirection()[2], 0.37944442);
    
    /*** GetNewPosition(), SetPosition() ***/
    Vector3D newpos1 = ((Carrier*)drone)->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    
    ((Carrier*)drone)->SetPosition(newpos);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[0], 251.18401);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[1], 127.4725);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetPosition()[2], -114.78968);
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
    ((Carrier*)drone)->SetRoute(route);

    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][0], 2.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][1], 0.0);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[0][2], 0.0);

    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][0], 168.8147);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][1], 85.335663);
    ASSERT_FLOAT_EQ(((Carrier*)drone)->GetRoute()[1][2], -76.84523);
  }


  TEST_F(CarrierTest, RobotConstructor) {
    //testing values set in constructor
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[2], 0.0);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(robot->GetDetails()).serialize(), picojson::value(obj_r).serialize());
  }

  TEST_F(CarrierTest, RobotSpeedTest) {
    /*** GetSpeed(), SetSpeed() ***/
    ASSERT_EQ(((Carrier*)robot)-> GetSpeed(), 30) << "get speed";
    ((Carrier*)robot)->SetSpeed(40);
    ASSERT_EQ(((Carrier*)robot)-> GetSpeed(), 40) << "new speed";
  }


  TEST_F(CarrierTest, RobotScheduleTest) {
    /*** IsScheduled(), SetScheduled() ***/
    ASSERT_EQ(((Carrier*)robot)->IsScheduled(), false) << "isscheduled";
    ((Carrier*)robot)->SetScheduled(true);
    ASSERT_EQ(((Carrier*)robot)->IsScheduled(), true) << "isscheduled";
  }


  TEST_F(CarrierTest, RobotVersionTest) {
    /*** GetVersion(), SetVersion() ***/
    ((Carrier*)robot)->SetVersion(1);
    ASSERT_EQ(((Carrier*)robot)->GetVersion(), 1) << "version";
  }


  TEST_F(CarrierTest, RobotPathTest) {
    /*** GetPath() ***/
    ASSERT_EQ(((Carrier*)robot)->GetPath(), "smart") << "get path";
  }


  TEST_F(CarrierTest, RobotBatteryTest) {
    /*** GetBattery() ***/
    ASSERT_NE(((Carrier*)robot)->GetBattery(), nullptr) << "getbattery";
  }


  TEST_F(CarrierTest, RobotReachNextPositionTest) {
    /*** ReachedNextPosition ***/
    ASSERT_EQ(((Carrier*)robot)->ReachedNextPosition(((Carrier*)robot)->GetPosition(), 1), true) << "reached next position";
  }


  TEST_F(CarrierTest, RobotPositionDirectionTests) {
    // SetUp
    std::vector<float> target;
    target.push_back(2);
    target.push_back(0);
    target.push_back(0);
    
    /*** GetNewDirection(), SetDirection() ***/
    Vector3D newdir1 = ((Carrier*)robot)->GetNewDirection(target);
    vector<float> newdir = newdir1.Convert();

    ((Carrier*)robot)->SetDirection(newdir);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[0], -0.82369328);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[1], -0.4213683);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetDirection()[2], 0.37944442);
    
    /*** GetNewPosition(), SetPosition() ***/
    Vector3D newpos1 = ((Carrier*)robot)->GetNewPosition(newdir1, 10);
    vector<float> newpos = newpos1.Convert();
    
    ((Carrier*)robot)->SetPosition(newpos);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[0], 251.18401);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[1], 127.4725);
    ASSERT_FLOAT_EQ(((Carrier*)robot)->GetPosition()[2], -114.78968);
  }


  TEST_F(CarrierTest, RobotRouteTest) {
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
    ((Carrier*)robot)->SetRoute(route);

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