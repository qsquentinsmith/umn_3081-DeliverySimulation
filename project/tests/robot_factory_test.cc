#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "robot_factory.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class RobotFactoryTest : public ::testing::Test {
   protected:
      Robot* robot;
      picojson::object obj;
      
    virtual void SetUp() {
        //setting up picojson::object for creat identity
      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "robot");
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
      robot = new Robot(position_to_add, direction_to_add, obj);
      
    }
    virtual void TearDown() {
      delete robot;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //Testing CreateEntity
  TEST_F(RobotFactoryTest, CreateEntityTest) {

    RobotFactory robotFactory;
    IEntity* robotFromFactory = robotFactory.CreateEntity(obj);

    /*** CreateEntity() ***/
    ASSERT_NE(robotFromFactory, nullptr);

    ASSERT_FLOAT_EQ(robot->GetPosition()[0], robotFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(robot->GetPosition()[1], robotFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(robot->GetPosition()[2], robotFromFactory->GetPosition().at(2));
    ASSERT_FLOAT_EQ(robot->GetDirection()[0], robotFromFactory->GetDirection().at(0));
    ASSERT_FLOAT_EQ(robot->GetDirection()[1], robotFromFactory->GetDirection().at(1));
    ASSERT_FLOAT_EQ(robot->GetDirection()[2], robotFromFactory->GetDirection().at(2));

  }

}  // namespace csci3081