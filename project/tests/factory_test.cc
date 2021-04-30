#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryTest, DroneCreated) {
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
  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], positionToAdd[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], positionToAdd[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], positionToAdd[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], directionToAdd[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], directionToAdd[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], directionToAdd[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
}

}  // namespace csci3081
