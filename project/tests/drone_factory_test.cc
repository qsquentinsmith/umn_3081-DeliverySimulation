#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone_factory.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class DroneFactoryTest : public ::testing::Test {
    protected:
    picojson::object obj;
    Drone* drone; 
    
    virtual void SetUp() {
      //setting up picojson::object for creat identity
      obj = JsonHelper::CreateJsonObject();
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
      drone = new Drone(positionToAdd, directionToAdd, obj);
    }
    virtual void TearDown() {
      delete drone;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(DroneFactoryTest, CreateEntityTest) {
    DroneFactory droneFactory;
    IEntity* droneFromFactory = droneFactory.CreateEntity(obj);

    /*** CreateEntity() ***/
    ASSERT_NE(droneFromFactory, nullptr);

    ASSERT_FLOAT_EQ(drone->GetPosition()[0], droneFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(drone->GetPosition()[1], droneFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(drone->GetPosition()[2], droneFromFactory->GetPosition().at(2));
    ASSERT_FLOAT_EQ(drone->GetDirection()[0], droneFromFactory->GetDirection().at(0));
    ASSERT_FLOAT_EQ(drone->GetDirection()[1], droneFromFactory->GetDirection().at(1));
    ASSERT_FLOAT_EQ(drone->GetDirection()[2], droneFromFactory->GetDirection().at(2));
  }

}  // namespace csci3081