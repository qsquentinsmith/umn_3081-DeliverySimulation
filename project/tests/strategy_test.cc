#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "istrategy.h"
#include "beeline.h"
#include "smart_path.h"
#include "parabolic.h"
#include "drone.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class StrategyTest : public ::testing::Test {
      

   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(StrategyTest, ParabolicTest) {
   
    //setting up picojson::object for creat identity
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
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
    Drone drone = Drone(positionToAdd, directionToAdd, obj);

    IStrategy* strategy = new Parabolic(); 

    std::vector<float> source;
    source.push_back(0);
    source.push_back(0);
    source.push_back(0);

    std::vector<float> target;
    target.push_back(100);
    target.push_back(0);
    target.push_back(100);

    std::vector<std::vector<float>> route = strategy->GetRoute(source, target);
    ASSERT_EQ(route.size(), 41) <<"check parabolic size";
  }


TEST_F(StrategyTest, Beeline) {

    //setting up picojson::object for creat identity
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
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
    Drone drone = Drone(positionToAdd, directionToAdd, obj);
    
    IStrategy* strategy = new Beeline(); 

    std::vector<float> source;
    source.push_back(0);
    source.push_back(0);
    source.push_back(0);

    std::vector<float> target;
    target.push_back(100);
    target.push_back(0);
    target.push_back(100);
    

    std::vector<std::vector<float>> route = strategy->GetRoute(source, target);

    ASSERT_EQ(route.size(), 4) << "Check beeline size";

  }


}  // namespace csci3081