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
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing CreateEntity
  TEST_F(DroneFactoryTest, CreateEntityTest) {

    //setting up picojson::object for creat identity
    picojson::object obj = JsonHelper::CreateJsonObject();
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
    Drone drone = Drone(position_to_add, direction_to_add, obj);

    DroneFactory droneFactory;
    IEntity* droneFromFactory = droneFactory.CreateEntity(obj);

    //checks that factory didnt return a nullptr
    //ASSERT_NE(drone, nullptr);

    // checking if values are set properly
    ASSERT_FLOAT_EQ(drone.GetPosition()[0], droneFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(drone.GetPosition()[1], droneFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(drone.GetPosition()[2], droneFromFactory->GetPosition().at(2));
    ASSERT_FLOAT_EQ(drone.GetDirection()[0], droneFromFactory->GetDirection().at(0));
    ASSERT_FLOAT_EQ(drone.GetDirection()[1], droneFromFactory->GetDirection().at(1));
    ASSERT_FLOAT_EQ(drone.GetDirection()[2], droneFromFactory->GetDirection().at(2));

  }

}  // namespace csci3081